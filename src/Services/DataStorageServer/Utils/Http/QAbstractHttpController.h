#pragma once
#include <QHttpServerResponse>
#include <QHttpServerRequest>

namespace utils {
template<typename...Args>
struct QAbstractHttpController {
    Q_DISABLE_COPY(QAbstractHttpController);
    virtual QHttpServerResponse handle(const Args&...) = 0;
    virtual ~QAbstractHttpController() = default;
    QAbstractHttpController() = default;
};
}
