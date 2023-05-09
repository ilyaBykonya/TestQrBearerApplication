#include "QrCodeDialog.h"
#include "QrCodeWidget.h"
#include <QVBoxLayout>
#include <QUuid>

QrCodeDialog::QrCodeDialog(const QByteArray &data, QWidget* parent)
    :QDialog{ parent } {
    this->setMinimumSize({ 100, 100 });
    auto codeView = new QrCodeWidget{ QtQrCode{ data } };
    auto layout = new QVBoxLayout{};
    layout->addWidget(codeView);
    this->setLayout(layout);
}

