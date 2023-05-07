#pragma once
#include <QDataStream>
#include <QByteArray>
#include <QDateTime>
#include <QSettings>
#include <QString>
#include <QMap>

namespace storages {
class TokenRepository {
private:
    static inline constexpr const char* s_tokens = "tokens";
    QSettings m_storage;
public:
    TokenRepository(const QString& path = {});
public:
    bool isValidToken(const QUuid& token);
    QMap<QUuid, QDateTime> tokens();
public:
    QUuid createToken(const QDateTime& expiration);
    void removeToken(const QUuid& token);
private:
    void removeExpiredTokens();
};
}
