#include "vectorlistmodel.h"

VectorListModel::VectorListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int VectorListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return _vecList.size();
}

bool VectorListModel::hasChildren(const QModelIndex &parent) const
{
    return false;
}

bool VectorListModel::canFetchMore(const QModelIndex &parent) const
{
    // FIXME: Implement me!
    return false;
}

void VectorListModel::fetchMore(const QModelIndex &parent)
{
    // FIXME: Implement me!
}

QVariant VectorListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole: {
        VecLib::Vector curr = _vecList.at(index.row());
        QString displayStr = tr(curr.getName().c_str()) + tr(" [")
                             + tr(std::to_string(curr.size()).c_str()) + tr("]( ");

        int j = 0;
        for (auto i : curr) {
            displayStr += tr(std::to_string(i).c_str());
            if (j < curr.size() - 1) {
                displayStr += tr(", ");
                j++;
            }
        }

        displayStr += tr(" )");

        return displayStr;
    }

    case VectorRole:
        return QVariant::fromValue(_vecList.at(index.row()));
    }

    // FIXME: Implement me!
    return QVariant();
}

bool VectorListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == VectorRole) {
            _vecList[index.row()] = value.value<VecLib::Vector>();
        }
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags VectorListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

bool VectorListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    for (int i = 0; i < count; i++)
        _vecList.insert(row, VecLib::Vector("sample", 1, 0.)); //!!!

    endInsertRows();
    return true;
}

bool VectorListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    _vecList.remove(row, count); //!!!

    endRemoveRows();
    return true;
}

QHash<int, QByteArray> VectorListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[VectorRole] = "vector";
    return roles;
}

QString VectorListModel::formConfig()
{
    QString cfg = tr("");

    for (auto &i : _vecList) {
        QString line = tr(i.getName().c_str()) + tr(" ") + tr("[")
                       + tr(std::to_string(i.size()).c_str()) + tr("] (");

        for (unsigned long j = 0; j < i.size(); j++) {
            line += tr(std::to_string(i.at(j)).c_str());
            if (j < i.size() - 1)
                line += tr(", ");
        }
        line += ")\n";
        cfg += line;
    }

    return cfg;
}

VecLib::Vector VectorListModel::find(std::string name)
{
    for (auto& i : _vecList)
    {
        if (i.getName() == name)
            return i;
    }

    throw (std::string("have not found: ") + name).c_str();
}
