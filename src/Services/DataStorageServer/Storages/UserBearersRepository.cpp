#include "UserBearersRepository.h"
#include <QUuid>

namespace storages {
UserBearersRepository::UserBearersRepository(const QString &path)
    :m_storage{ path, QSettings::Format::IniFormat } { m_storage.beginGroup(s_bearers); }

QDateTime UserBearersRepository::expirationOf(const QUuid &bearer) const {
    return m_storage.value(bearer.toString()).toDateTime();
}
bool UserBearersRepository::isAvailableBearer(const QUuid &bearer) {
    if(not m_storage.contains(bearer.toString())) {
        return false;
    } else if(isExpireDateTime(m_storage.value(bearer.toString()).toDateTime())) {
        removeBearer(bearer);
        return false;
    } else {
        return true;
    }
}
QMap<QUuid, QDateTime> UserBearersRepository::allBearers() const {
    QMap<QUuid, QDateTime> result{};
    for(const auto& key: m_storage.allKeys())
        result[QUuid::fromString(key)] = m_storage.value(key).toDateTime();

    return result;
}

QUuid UserBearersRepository::createNewBearer(const QDateTime& expiration) {
    const auto bearer = QUuid::createUuid();
    m_storage.setValue(bearer.toString(), expiration);
    return bearer;
}
void UserBearersRepository::removeBearer(const QUuid &bearer) {
    m_storage.remove(bearer.toString());
}

bool UserBearersRepository::isExpireDateTime(const QDateTime &expiration) {
    return QDateTime::currentDateTime() > expiration;
}
}
