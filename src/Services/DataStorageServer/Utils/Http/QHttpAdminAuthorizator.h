#pragma once
#include "QHttpServerMiddleware.h"


namespace utils {
template<typename...Args>
class QHttpAdminAuthorizator: public QAbstractHttpController<QString, Args...> {
private:
    std::function<QHttpServerResponse(const Args&...)> m_next;
    QString m_code;
public:
    QHttpAdminAuthorizator(QString code, const std::function<QHttpServerResponse(const Args&...)>& next)
        :m_next{ std::move(next) }, m_code{ code } {}
public:
    virtual QHttpServerResponse handle(const QString& code, const Args&...request) override {
        if(m_code != code)
            return QHttpServerResponse::StatusCode::Unauthorized;

        return m_next(request...);
    }
};
}
