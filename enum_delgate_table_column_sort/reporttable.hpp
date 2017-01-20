#ifndef CSV_TOOLS_REPORTTABLE_H
#define CSV_TOOLS_REPORTTABLE_H

#include <QTableView>
#include <map>
#include "idtypedelegate.hpp"
#include "reportmodel.hpp"

class QAction;
class QSortFilterProxyModel;

class ReportTable : public QTableView
{
    Q_OBJECT

public:
    explicit ReportTable(QWidget *parent, const ReportModel&);
    virtual ~ReportTable() {}

private:
    QSortFilterProxyModel* mProxyModel;
    ReportModel& mModel;
    IdTypeDelegate mIdTypeDelegate;
};

#endif
