#include <QtQrCodePainter>
#include <QtQrCode>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTimer>

int main(int argc, char *argv[]) {
    QApplication app{ argc, argv };
    QLabel window;

    auto timer = new QTimer{};
    QObject::connect(timer, &QTimer::timeout, [&window] {
        window.setPixmap(QPixmap::fromImage(QtQrCodePainter{}.toImage(QtQrCode{ "dqwegwrh" }, 200)));
    });
    timer->start(1000);

    window.show();
    return app.exec();
}
