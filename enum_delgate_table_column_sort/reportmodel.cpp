#include "reportmodel.hpp"

ReportModel::ReportModel(QObject* parent)
: QAbstractItemModel(parent)
{
}

QModelIndex ReportModel::index(int, int, const QModelIndex &) const
{
    return QModelIndex();
}

QModelIndex ReportModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int ReportModel::rowCount(const QModelIndex &parent) const
{
    return mRows.size();
}

int ReportModel::columnCount(const QModelIndex &) const
{
    return mColumnDescription+1;
}

QVariant ReportModel::data(const QModelIndex &index, int role) const
{
    if (role!=Qt::DisplayRole)
        return QVariant();

    //switch (index.column())
}
