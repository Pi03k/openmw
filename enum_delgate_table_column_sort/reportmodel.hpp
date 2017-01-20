#pragma once

#include "row.hpp"
#include <vector>
#include <QAbstractItemModel>
#include <QModelIndex>

class ReportModel : public QAbstractItemModel
{
public:
    explicit ReportModel(QObject* parent);
    virtual QModelIndex index(int, int, const QModelIndex &) const;
    virtual QModelIndex parent(const QModelIndex &) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
private:
    std::vector<Row> mRows;
};  // class Model
