#pragma once
#include "Storages/UserBearersRepository.h"
#include <QHttpServerResponse>
#include <memory>

namespace controllers {
class BearersController {
private:
    std::shared_ptr<storages::UserBearersRepository> m_bearers;
public:
    BearersController(const std::shared_ptr<storages::UserBearersRepository> &bearers);
public:
    QHttpServerResponse createNewUserBearer(quint64 expirationSpan);
    QHttpServerResponse removeBearer(const QByteArray& bearer);
    QHttpServerResponse getAllBearers();
};
}


