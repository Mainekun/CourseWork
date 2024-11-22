#ifndef OPERATORLISTMODEL_H
#define OPERATORLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <QString>
#include <QVariant>

class OperatorListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum class OPTYPE
    {
        MININDECIES,
        MAXINDECIES,
        ELEMSUM,
        ELEMPROD,
        SORTASC,
        SORTDESC,
        REVERSE,
        LCD,
        RCM
    };

    explicit OperatorListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QStringList opers;
};

#endif // OPERATORLISTMODEL_H
