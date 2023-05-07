#include "TokenController.h"
#include <QJsonObject>
#include <QUuid>

namespace controllers {
TokenController::TokenController(const std::shared_ptr<storages::TokenRepository> &tokens)
    :m_tokens{ std::move(tokens) } { }

QHttpServerResponse TokenController::createToken(quint64 expirationSpan) {
    return QHttpServerResponse{ m_tokens->createToken(QDateTime::currentDateTime().addSecs(expirationSpan)).toString() };
}
QHttpServerResponse TokenController::removeToken(const QByteArray &bearer) {
    m_tokens->removeToken(QUuid::fromString(bearer));
    return QHttpServerResponse{ QHttpServerResponse::StatusCode::Accepted };
}
QHttpServerResponse TokenController::getAllTokens() {
    QJsonObject result{};
    const auto elements = m_tokens->tokens();
    for(auto iter = elements.begin(); iter != elements.end(); ++iter)
        result[iter.key().toString(QUuid::StringFormat::WithoutBraces)] = iter.value().toSecsSinceEpoch();

    return result;
}
}
