#include "TokenRepository.h"
#include <QUuid>

namespace storages {
TokenRepository::TokenRepository(const QString &path)
    :m_storage{ path, QSettings::Format::IniFormat } { m_storage.beginGroup(s_tokens); }


bool TokenRepository::isValidToken(const QUuid &token) {
    removeExpiredTokens();
    return m_storage.contains(token.toString());
}
QMap<QUuid, QDateTime> TokenRepository::tokens() {
    removeExpiredTokens();
    QMap<QUuid, QDateTime> result{};
    for(const auto& key: m_storage.allKeys())
        result[QUuid::fromString(key)] = m_storage.value(key).toDateTime();

    return result;
}

QUuid TokenRepository::createToken(const QDateTime& expiration) {
    removeExpiredTokens();
    const auto token = QUuid::createUuid();
    m_storage.setValue(token.toString(), expiration);
    return token;
}
void TokenRepository::removeToken(const QUuid &token) {
    removeExpiredTokens();
    m_storage.remove(token.toString());
}

void TokenRepository::removeExpiredTokens() {
    const auto current = QDateTime::currentDateTime();
    for(const auto& key: m_storage.allKeys())
        if(current > m_storage.value(key).toDateTime())
            m_storage.remove(key);
}
}
