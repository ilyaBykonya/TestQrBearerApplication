#include <QCoreApplication>
#include <QtHttpServer>
#include <QPixmap>
#include <QImage>
#include "Storages/TokenRepository.h"
#include "Storages/ImageRepository.h"
#include "Controllers/TokenController.h"
#include "Controllers/ImageController.h"
#include "Utils/Http/TokenAuthorizator.h"
#include <ranges>
using namespace controllers;
using namespace storages;
using namespace utils;

int main(int argc, char *argv[]) {
    QCoreApplication app{ argc, argv };
    if(app.arguments().size() == 2)
        qFatal("Use app: <app-name> <image-dir> <tokens-storage>");

    auto images = std::make_shared<ImageRepository>(argv[1]);
    auto tokens = std::make_shared<TokenRepository>(argv[2]);
    auto server = std::make_shared<QHttpServer>();

    auto imageController = std::make_shared<ImageController>(images);
    auto tokenController = std::make_shared<TokenController>(tokens);

    auto getAllTokens = std::make_shared<TokenAuthorizator<>>(tokens,
        [tokenController]() { return tokenController->getAllTokens(); });
    auto createToken = std::make_shared<TokenAuthorizator<quint64>>(tokens,
        [tokenController](quint64 expiration) { return tokenController->createToken(expiration); });
    auto removeToken = std::make_shared<TokenAuthorizator<QByteArray>>(tokens,
        [tokenController](const QByteArray& token) { return tokenController->removeToken(token); });

    auto getImagesList = std::make_shared<TokenAuthorizator<>>(tokens,
        [imageController]() { return imageController->imagesList(); });
    auto getImage = std::make_shared<TokenAuthorizator<QString>>(tokens,
        [imageController](const QString& image) { return imageController->image(image); });


    server->route("/auth/token/all/", [getAllTokens](const QHttpServerRequest& request) {
        return getAllTokens->handle(request);
    });
    server->route("/auth/token/create/<arg>", [createToken](quint64 expirationSpan, const QHttpServerRequest& request) {
        return createToken->handle(expirationSpan, request);
    });
    server->route("/auth/token/remove/<arg>", [removeToken](const QByteArray& token, const QHttpServerRequest& request) {
        return removeToken->handle(token, request);
    });

    server->route("/data/images/list", [getImagesList](const QHttpServerRequest& request) {
        return getImagesList->handle(request);
    });
    server->route("/data/images/<arg>", [getImage](const QString& image, const QHttpServerRequest& request) {
        return getImage->handle(image, request);
    });

    server->setMissingHandler([](const QHttpServerRequest &request, QHttpServerResponder &&responder) {
        responder.sendResponse("fuck");
    });

    server->listen(QHostAddress::SpecialAddress::Any, 5555);
    return app.exec();
}







