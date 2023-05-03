#pragma once
#include <QStringList>
#include <QImage>
#include <QDir>

namespace storages {
class ImageRepository {
private:
    QDir m_root;
public:
    ImageRepository(const QString &root = QDir::rootPath());
public:
    QImage image(const QString& name);
    QStringList images() const;
};
}

