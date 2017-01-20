#include "reporttable.hpp"

#include <algorithm>

#include <QAction>
#include <QContextMenuEvent>
#include <QEvent>
#include <QHeaderView>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QTextDocument>

#include "universalid.hpp"
#include "idtypedelegate.hpp"

ReportTable::ReportTable(QWidget *parent, const ReportModel& reportModel)
: QTableView(parent)
, mModel(reportModel)
, mIdTypeDelegate(this)
{
    horizontalHeader()->setSectionResizeMode (QHeaderView::Interactive);
    horizontalHeader()->setStretchLastSection (true);
    verticalHeader()->hide();
    setSortingEnabled (true);
    setSelectionBehavior (QAbstractItemView::SelectRows);
    setSelectionMode (QAbstractItemView::ExtendedSelection);

    //mProxyModel = new IdTableProxyModel (this);
    //mProxyModel->setSourceModel (mModel);
    setModel (&mModel);
    //mProxyModel->setDynamicSortFilter(true);

    //setColumnHidden (2, true);

    //mIdTypeDelegate = new IdTypeDelegate(this); //Factory().makeDelegate(NULL, mDocument, this);

	//TODO pi03k: read QT doc about this method.
    setItemDelegateForColumn (0, &mIdTypeDelegate);

}

/*std::vector<int> ReportTable::getReplaceIndices (bool selection) const
{
    std::vector<int> indices;

    if (selection)
    {
        QModelIndexList selectedRows = selectionModel()->selectedRows();

        std::vector<int> rows;

        for (QModelIndexList::const_iterator iter (selectedRows.begin()); iter!=selectedRows.end();
            ++iter)
        {
            rows.push_back (mProxyModel->mapToSource (*iter).row());
        }

        std::sort (rows.begin(), rows.end());

        for (std::vector<int>::const_iterator iter (rows.begin()); iter!=rows.end(); ++iter)
        {
            QString hint = mModel->data (mModel->index (*iter, 2)).toString();

            if (!hint.isEmpty() && hint[0]=='R')
                indices.push_back (*iter);
        }
    }
    else
    {
        for (int i=0; i<mModel->rowCount(); ++i)
        {
            QString hint = mModel->data (mModel->index (i, 2)).toString();

            if (!hint.isEmpty() && hint[0]=='R')
                indices.push_back (i);
        }
    }

    return indices;
}*/

/*
void ReportTable::stateChanged (int state, Document *document)
{
    if (mRefreshAction)
        mRefreshAction->setEnabled (!(state & mRefreshState));
}
*/
