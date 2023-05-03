#include "UserBearersView.h"
#include "BearerQrCore/BearerQrCodeMessageBox.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QJsonObject>

UserBearersView::UserBearersView(const QString& code, QWidget* parent)
    :QWidget{ parent },
    m_manager{ new QNetworkAccessManager{} },
    m_bearers{ new UserBearersModel{} },
    m_view{ new QListView{} },
    m_code{ code } {
        m_view->setModel(m_bearers);
        auto showBearerButton = new QPushButton{ "*" };
        auto createBearerButton = new QPushButton{ "+" };
        auto removeBearerButton = new QPushButton{ "-" };

        connect(m_view, &QAbstractItemView::doubleClicked, this, &UserBearersView::showBearer);
        connect(showBearerButton, &QPushButton::clicked, this, &UserBearersView::showBearer);
        connect(createBearerButton, &QPushButton::clicked, this, &UserBearersView::createBearer);
        connect(removeBearerButton, &QPushButton::clicked, this, &UserBearersView::removeBearer);

        auto layout = new QVBoxLayout{};
            auto buttonLayout = new QHBoxLayout{};
            buttonLayout->addWidget(createBearerButton);
            buttonLayout->addWidget(removeBearerButton);
            buttonLayout->addWidget(showBearerButton);
            buttonLayout->addStretch(1);
        layout->addLayout(buttonLayout, 0);
        layout->addWidget(m_view, 1);
        this->setLayout(layout);
        resetBearersModel();
}

void UserBearersView::showBearer() {
    const auto selection = m_view->selectionModel()->selection();
    if(selection.size() != 1)
        return;

    const auto bearer = m_bearers->bearer(selection.indexes().front().row());
    BearerQrCodeMessageBox qrCoreView{ bearer, this };
    qrCoreView.showMaximized();
    qrCoreView.exec();
}
void UserBearersView::createBearer() {
    const auto request = QNetworkRequest{ QString{ "%1/%2/%3/%4" }.arg(s_address).arg("create").arg(m_code).arg(24 * 60 * 60) };
    auto reply = std::shared_ptr<QNetworkReply>{ m_manager->get(request) };
    connect(reply.get(), &QNetworkReply::finished, [this, reply] {
        this->resetBearersModel();
    });
}
void UserBearersView::removeBearer() {
    const auto selection = m_view->selectionModel()->selection();
    if(selection.size() != 1)
        return;

    //QMessageBox::information(this, "remove", selection.indexes().front().data().toString());
    const auto element = m_bearers->bearer(selection.indexes().front().row()).toString(QUuid::StringFormat::WithoutBraces);
    const auto request = QNetworkRequest{ QString{ "%1/%2/%3/%4" }.arg(s_address).arg("remove").arg(m_code).arg(element) };
    auto reply = std::shared_ptr<QNetworkReply>{ m_manager->get(request) };
    connect(reply.get(), &QNetworkReply::finished, [this, reply] {
        this->resetBearersModel();
    });
}

void UserBearersView::resetBearersModel() {
    const auto request = QNetworkRequest{ QString{ "%1/%2/%3" }.arg(s_address).arg("all").arg(m_code) };
    auto reply = std::shared_ptr<QNetworkReply>{ m_manager->get(request) };
    connect(reply.get(), &QNetworkReply::finished, [this, reply] {
        this->parseBearersModel(QJsonDocument::fromJson(reply->readAll()));
    });
}
void UserBearersView::parseBearersModel(const QJsonDocument& model) {
    QMap<QUuid, QDateTime> bearers{};
    const auto modelObject = model.object();
    for(auto iter = modelObject.begin(); iter != modelObject.end(); ++iter)
        bearers[QUuid::fromString(iter.key())] = QDateTime::fromSecsSinceEpoch(iter.value().toInteger());
    m_bearers->resetBearersTable(bearers);
}






























