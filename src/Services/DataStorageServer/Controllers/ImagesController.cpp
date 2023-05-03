#include "ImagesController.h"
#include <QJsonArray>
#include <QBuffer>

namespace controllers {
ImagesController::ImagesController(const std::shared_ptr<storages::ImageRepository> &images)
    :m_images{ std::move(images) } {}

QHttpServerResponse ImagesController::image(const QString &name) const {
    QByteArray result{};
    QBuffer buffer{ &result };
    m_images->image(name).save(&buffer, "PNG");
    return QHttpServerResponse{ result };
}
QHttpServerResponse ImagesController::imagesList() const {
    return QHttpServerResponse{ QJsonArray::fromStringList(m_images->images()) };
}
}
