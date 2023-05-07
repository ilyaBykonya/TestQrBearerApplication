#pragma once
#include <QHttpServerResponse>
#include <QHttpServerRequest>

namespace utils {
template<typename...Args>
struct AbstractHttpController {
    Q_DISABLE_COPY(AbstractHttpController);
    virtual QHttpServerResponse handle(const Args&...) = 0;
    virtual ~AbstractHttpController() = default;
    AbstractHttpController() = default;
};
}
