#pragma once
#include "UserBearersModel/UserBearersModel.h"
#include <QNetworkAccessManager>
#include <QItemSelectionModel>
#include <QJsonDocument>
#include <QPushButton>
#include <QListView>
#include <QPointer>
#include <QWidget>

class UserBearersView: public QWidget {
private:
    inline static const QString s_address = "http://127.0.0.1:5555/auth/bearer";
private:
    QPointer<QNetworkAccessManager> m_manager;
    QPointer<UserBearersModel> m_bearers;
    QPointer<QListView> m_view;
    QString m_code;
public:
    UserBearersView(const QString& code, QWidget* parent = nullptr);
private slots:
    void showBearer();
    void createBearer();
    void removeBearer();
private slots:
    void resetBearersModel();
    void parseBearersModel(const QJsonDocument&);
};

