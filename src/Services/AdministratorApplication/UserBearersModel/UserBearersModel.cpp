#include "UserBearersModel.h"

UserBearersModel::UserBearersModel(QObject *parent)
    :QAbstractListModel{ parent } {}
int UserBearersModel::rowCount(const QModelIndex &parent) const {
    return m_bearers.size();
}

QVariant UserBearersModel::data(const QModelIndex &index, int role) const {
    if(not index.isValid()) return {};
    if(role != Qt::ItemDataRole::DisplayRole) return {};

    const auto item = std::next(m_bearers.begin(), index.row());
    return QString{ "[%1:%2]" }.arg(item.key().toString()).arg(item.value().toString());
}

void UserBearersModel::resetBearersTable(const QMap<QUuid, QDateTime> &bearers) {
    beginResetModel();
    m_bearers = bearers;
    endResetModel();
}

QDateTime UserBearersModel::expiration(int index) const {
    return std::next(m_bearers.begin(), index).value();
}
QUuid UserBearersModel::bearer(int index) const {
    return std::next(m_bearers.begin(), index).key();
}
