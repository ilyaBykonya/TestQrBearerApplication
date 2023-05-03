#pragma once
#include <QDataStream>
#include <QByteArray>
#include <QDateTime>
#include <QSettings>
#include <QString>
#include <QMap>

namespace storages {
class UserBearersRepository {
private:
    static inline constexpr const char* s_bearers = "bearers";
    QSettings m_storage;
public:
    UserBearersRepository(const QString& path = {});
public:
    QDateTime expirationOf(const QUuid& bearer) const;
    bool isAvailableBearer(const QUuid& bearer);
    QMap<QUuid, QDateTime> allBearers() const;
public:
    QUuid createNewBearer(const QDateTime& expiration);
    void removeBearer(const QUuid& bearer);
private:
    static bool isExpireDateTime(const QDateTime& expiration);
};
}
