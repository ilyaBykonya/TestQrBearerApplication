#include "BearersController.h"
#include <QJsonObject>
#include <QUuid>

namespace controllers {
BearersController::BearersController(const std::shared_ptr<storages::UserBearersRepository> &bearers)
    :m_bearers{ std::move(bearers) } { }

QHttpServerResponse BearersController::createNewUserBearer(quint64 expirationSpan) {
    return QHttpServerResponse{ m_bearers->createNewBearer(QDateTime::currentDateTime().addSecs(expirationSpan)).toRfc4122() };
}
QHttpServerResponse BearersController::removeBearer(const QByteArray &bearer) {
    m_bearers->removeBearer(QUuid::fromString(bearer));
    return QHttpServerResponse{ QHttpServerResponse::StatusCode::Accepted };
}
QHttpServerResponse BearersController::getAllBearers() {
    QJsonObject result{};
    const auto elements = m_bearers->allBearers();
    for(auto iter = elements.begin(); iter != elements.end(); ++iter)
        result[iter.key().toString(QUuid::StringFormat::WithoutBraces)] = iter.value().toSecsSinceEpoch();

    return result;
}
}
