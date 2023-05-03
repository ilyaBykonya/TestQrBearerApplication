#pragma once
#include <QtQrCode>
#include <QDialog>

class BearerQrCodeMessageBox : public QDialog {
public:
    BearerQrCodeMessageBox(const QUuid &bearer, QWidget* parent = nullptr);
};

