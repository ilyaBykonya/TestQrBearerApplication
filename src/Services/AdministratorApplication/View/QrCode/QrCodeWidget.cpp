#include "QrCodeWidget.h"
#include <QtQrCodePainter>

QrCodeWidget::QrCodeWidget(const QtQrCode &code, QWidget *parent)
    :QWidget{ parent }, m_code{ code } {}

void QrCodeWidget::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter painter{ this };
    QtQrCodePainter{}.paint(m_code, painter, width(), height());
}


