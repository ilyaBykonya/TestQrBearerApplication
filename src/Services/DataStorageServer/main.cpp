#include <QCoreApplication>
#include <QtHttpServer>
#include <QPixmap>
#include <QImage>
#include "Utils/Http/QHttpAdminAuthorizator.h"
#include "Storages/UserBearersRepository.h"
#include "Storages/ImageRepository.h"
#include "Controllers/BearersController.h"
#include "Controllers/ImagesController.h"
#include <ranges>
using namespace controllers;
using namespace storages;
using namespace utils;

int main(int argc, char *argv[]) {
    QCoreApplication app{ argc, argv };
    if(app.arguments().size() == 1)
        qFatal("Use app: <app-name> <admin-code>");

    auto bearers = std::make_shared<UserBearersRepository>("/home/the_gast/Dev/Projects/QtQrAuthentificationBearer/test-files-storage/user-bearers.txt");
    auto images = std::make_shared<ImageRepository>("/home/the_gast/");
    auto server = std::make_shared<QHttpServer>();

    const auto adminCode = app.arguments().at(1);
    auto imagesController = std::make_shared<ImagesController>(images);
    auto bearersController = std::make_shared<BearersController>(bearers);
    auto getAllBearers = std::make_shared<QHttpAdminAuthorizator<>>(adminCode,
        [bearersController]() { return bearersController->getAllBearers(); });
    auto removeBearer = std::make_shared<QHttpAdminAuthorizator<QByteArray>>(adminCode,
        [bearersController](const QByteArray& bearer) { return bearersController->removeBearer(bearer); });
    auto createBearer = std::make_shared<QHttpAdminAuthorizator<quint64>>(adminCode,
        [bearersController](quint64 expiration) { return bearersController->createNewUserBearer(expiration); });

    server->route("/time", []() {
        return QDateTime::currentDateTime().toString();
    });
    server->route("/auth/bearer/all/<arg>", [getAllBearers](const QString& code) {
        return getAllBearers->handle(code);
    });
    server->route("/auth/bearer/create/<arg>/<arg>", [createBearer](const QString& code, quint64 expirationSpan) {
        return createBearer->handle(code, expirationSpan);
    });
    server->route("/auth/bearer/remove/<arg>/<arg>", [removeBearer](const QString& code, const QByteArray& bearer) {
        return removeBearer->handle(code, bearer);
    });

    server->route("/data/images/list", [imagesController] {
        return imagesController->imagesList();
    });
    server->route("/data/images/<arg>", [imagesController](const QString& name) {
        return imagesController->image(name);
    });
    server->listen(QHostAddress::SpecialAddress::Any, 5555);
    return app.exec();
}







