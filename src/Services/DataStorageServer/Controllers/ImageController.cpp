#include "ImageController.h"
#include <QJsonArray>
#include <QBuffer>

namespace controllers {
ImageController::ImageController(const std::shared_ptr<storages::ImageRepository> &images)
    :m_images{ std::move(images) } {}

QHttpServerResponse ImageController::image(const QString &name) const {
    QByteArray result{};
    QBuffer buffer{ &result };
    m_images->image(name).save(&buffer, "PNG");
    return QHttpServerResponse{ result };
}
QHttpServerResponse ImageController::imagesList() const {
    return QHttpServerResponse{ QJsonArray::fromStringList(m_images->images()) };
}
}
