#include <QApplication>
#include <QNetworkReply>
#include "View/TokenView.h"

int main(int argc, char *argv[]) {
    QApplication app{ argc, argv };
    TokenView window{};

    window.show();
    return app.exec();
}
