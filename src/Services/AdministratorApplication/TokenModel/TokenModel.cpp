#include "TokenModel.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrl>

TokenModel::TokenModel(QObject* parent)
    :QAbstractListModel{ parent },
     m_manager{ new QNetworkAccessManager{ this } } {}
QPair<QUuid, QDateTime> TokenModel::tokenAt(qint32 index) const {
    const auto token = std::next(m_tokens.begin(), index);
    return { token.key(), token.value() };
}

void TokenModel::create(qint64 expirationSpan) {
    const auto request = QNetworkRequest{ QString{ "%1/%2/%3" }.arg(s_address).arg("create").arg(expirationSpan) };
    const auto reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, reply, &QObject::deleteLater);
    connect(reply, &QNetworkReply::finished, this, &TokenModel::refresh);
}
void TokenModel::remove(const QUuid &token) {
    const auto request = QNetworkRequest{ QString{ "%1/%2/%3" }.arg(s_address).arg("remove").arg(token.toString(QUuid::StringFormat::WithoutBraces)) };
    const auto reply = m_manager->get(request);
    connect(reply, &QNetworkReply::finished, reply, &QObject::deleteLater);
    connect(reply, &QNetworkReply::finished, this, &TokenModel::refresh);
}
void TokenModel::refresh() {
    qDebug() << "Send refresh request";
    const auto reply = m_manager->get(QNetworkRequest{ { "http://127.0.0.1:5555/auth/token/all/" } });
    QObject::connect(reply, &QNetworkReply::finished, [this, reply]{
        const auto result = QJsonDocument::fromJson(reply->readAll());
        this->parseTokensFromJson(result);
        reply->deleteLater();
    });
}

int TokenModel::rowCount(const QModelIndex&/*parent*/) const {
    return m_tokens.size();
}
QVariant TokenModel::data(const QModelIndex &index, int role) const {
    if(not index.isValid()) return {};
    if(role != Qt::ItemDataRole::DisplayRole) return {};

    const auto item = std::next(m_tokens.begin(), index.row());
    return QString{ "[%1 <=> %2]" }.arg(item.key().toString(), item.value().toString());
}

void TokenModel::parseTokensFromJson(const QJsonDocument& document) {
    this->beginResetModel();
    m_tokens.clear();
    const auto tokens = document.object();
    for(const auto& token: tokens.keys())
        m_tokens.insert(QUuid::fromString(token), QDateTime::fromSecsSinceEpoch(tokens[token].toInteger()));

    this->endResetModel();
}


