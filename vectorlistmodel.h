#ifndef VECTORLISTMODEL_H
#define VECTORLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVariant>
#include "vectorLib/vector.h"

class VectorListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit VectorListModel(QObject *parent = nullptr);

    enum Roles {
        VectorRole = Qt::UserRole + 1,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool hasChildren(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const;

    QString formConfig();

    VecLib::Vector find(std::string);

private:
    QList<VecLib::Vector> _vecList;
};

#endif // VECTORLISTMODEL_H
