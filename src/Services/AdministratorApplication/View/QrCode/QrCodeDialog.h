#pragma once
#include <QtQrCode>
#include <QDialog>

class QrCodeDialog : public QDialog {
public:
    QrCodeDialog(const QByteArray &data, QWidget* parent = nullptr);
};

