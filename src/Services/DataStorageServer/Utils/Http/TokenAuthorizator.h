#pragma once
#include "Storages/TokenRepository.h"
#include "AbstractHttpController.h"
#include <QUuid>

namespace utils {
template<typename...Args>
class TokenAuthorizator: public AbstractHttpController<Args..., QHttpServerRequest> {
private:
    std::function<QHttpServerResponse(const Args&...)> m_next;
    std::shared_ptr<storages::TokenRepository> m_tokens;
public:
    TokenAuthorizator(std::shared_ptr<storages::TokenRepository> tokens, const std::function<QHttpServerResponse(const Args&...)>& next)
        :m_next{ std::move(next) }, m_tokens{ tokens } {}
public:
    virtual QHttpServerResponse handle(const Args&...parametes, const QHttpServerRequest& request) override {
        qDebug() << "Request";
        if(not request.remoteAddress().isLoopback())
            if(not m_tokens->isValidToken(QUuid::fromString(request.value("Authorization"))))
                return QHttpServerResponse::StatusCode::Unauthorized;

        qDebug() << "\tSuccess";
        return m_next(parametes...);
    }
};
}
