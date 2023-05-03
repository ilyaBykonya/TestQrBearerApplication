#pragma once
#include <QAbstractListModel>
#include <QDateTime>
#include <QPointer>
#include <QUuid>

class UserBearersModel : public QAbstractListModel {
private:
    Q_OBJECT
private:
    QMap<QUuid, QDateTime> m_bearers;
public:
    explicit UserBearersModel(QObject *parent = nullptr);
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
public:
    void resetBearersTable(const QMap<QUuid, QDateTime>& bearers);
    QDateTime expiration(int index) const;
    QUuid bearer(int index) const;
};

