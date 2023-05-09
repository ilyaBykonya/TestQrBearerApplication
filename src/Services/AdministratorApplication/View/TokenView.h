#pragma once
#include "TokenModel/TokenModel.h"
#include <QNetworkAccessManager>
#include <QItemSelectionModel>
#include <QJsonDocument>
#include <QPushButton>
#include <QListView>
#include <QPointer>
#include <QWidget>

class TokenView: public QWidget {
private:
    QPointer<TokenModel> m_tokens;
    QPointer<QListView> m_view;
public:
    TokenView(QWidget* parent = nullptr);
private slots:
    void showToken();
    void createToken();
    void removeToken();
};

