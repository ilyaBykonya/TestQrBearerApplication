#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QListView>
#include "UserBearersModel/UserBearersModel.h"
#include "View/UserBearersView.h"

int main(int argc, char *argv[]) {
    QApplication app{ argc, argv };
    if(app.arguments().size() == 1)
        qFatal("Use app: <app-name> <admin-code>");

    auto view = new UserBearersView{ app.arguments().at(1) };
    view->show();

    return app.exec();
}
