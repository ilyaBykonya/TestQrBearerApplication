#pragma once
#include <QtQrCode>
#include <QWidget>


class QrCodeWidget: public QWidget {
private:
    QtQrCode m_code;
public:
    QrCodeWidget(const QtQrCode &code = {}, QWidget *parent = nullptr);
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

