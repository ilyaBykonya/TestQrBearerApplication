#pragma once
#include "Storages/ImageRepository.h"
#include <QHttpServerResponse>
#include <memory>

namespace controllers {
class ImagesController {
private:
    std::shared_ptr<storages::ImageRepository> m_images;
public:
    ImagesController(const std::shared_ptr<storages::ImageRepository> &images);
public:
    QHttpServerResponse image(const QString& name) const;
    QHttpServerResponse imagesList() const;
};
}
