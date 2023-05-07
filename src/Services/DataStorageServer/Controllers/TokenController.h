#pragma once
#include "Storages/TokenRepository.h"
#include <QHttpServerResponse>
#include <memory>

namespace controllers {
class TokenController {
private:
    std::shared_ptr<storages::TokenRepository> m_tokens;
public:
    TokenController(const std::shared_ptr<storages::TokenRepository> &tokens);
public:
    QHttpServerResponse createToken(quint64 expirationSpan);
    QHttpServerResponse removeToken(const QByteArray& token);
    QHttpServerResponse getAllTokens();
};
}


