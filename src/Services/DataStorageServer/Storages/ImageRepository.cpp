#include "ImageRepository.h"



namespace storages {
ImageRepository::ImageRepository(const QString &root)
    :m_root{ root } { m_root.setNameFilters(QStringList{} << "*.png" << "*.jpg" << "*.jpeg"); }

QImage ImageRepository::image(const QString &name) {
    return QImage{ m_root.filePath(name) };
}
QStringList ImageRepository::images() const {
    return m_root.entryList(QDir::Filter::Files | QDir::Filter::Readable);
}
}
