#pragma once
#include <QNetworkAccessManager>
#include <QAbstractListModel>
#include <QDateTime>
#include <QPointer>
#include <QUuid>

class TokenModel: public QAbstractListModel {
private:
    inline static const QString s_address = "http://127.0.0.1:5555/auth/token";
    QPointer<QNetworkAccessManager> m_manager;
    QMap<QUuid, QDateTime> m_tokens;
public:
    TokenModel(QObject* parent = nullptr);
public:
    QPair<QUuid, QDateTime> tokenAt(qint32 index) const;
public:
    void create(qint64 expirationSpan);
    void remove(const QUuid& token);
    void refresh();
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
private:
    void parseTokensFromJson(const QJsonDocument& document);
};
