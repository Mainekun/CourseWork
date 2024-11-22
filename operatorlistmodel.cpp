#include "operatorlistmodel.h"

OperatorListModel::OperatorListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    opers = {};
}

int OperatorListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return opers.size();
}

QVariant OperatorListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
    case Qt::DisplayRole:
        return QVariant::fromValue(opers.at(index.row));
    }

    return QVariant();
}
