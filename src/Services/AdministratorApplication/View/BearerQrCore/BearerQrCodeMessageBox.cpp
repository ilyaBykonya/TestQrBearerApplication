#include "BearerQrCodeMessageBox.h"
#include "QrCodeWidget.h"
#include <QVBoxLayout>
#include <QUuid>

BearerQrCodeMessageBox::BearerQrCodeMessageBox(const QUuid &bearer, QWidget* parent)
    :QDialog{ parent } {
        this->setMinimumSize({ 100, 100 });
        auto codeView = new QrCodeWidget{ QtQrCode{ bearer.toRfc4122() } };
        auto layout = new QVBoxLayout{};
        layout->addWidget(codeView);
        this->setLayout(layout);
    }
