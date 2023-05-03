#pragma once
#include "QAbstractHttpController.h"
#include <memory>

namespace utils {
template<typename...Args>
class QHttpServerMiddleware: public QAbstractHttpController<Args...> {
private:
    std::shared_ptr<QAbstractHttpController<Args...>> m_next;
public:
    QHttpServerResponse handleOnNext(const Args&... request) {
        return m_next(request...);
    }
    QHttpServerMiddleware(std::shared_ptr<QAbstractHttpController<Args...>> next)
        :m_next{ std::move(next) } {}
public:
    virtual ~QHttpServerMiddleware() = default;
};
}
