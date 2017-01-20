#ifndef IDTYPEDELEGATE_HPP
#define IDTYPEDELEGATE_HPP

#include <QPainter>
#include <QSize>
#include <QStyledItemDelegate>

class IdTypeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit IdTypeDelegate(QObject *parent);
    ~IdTypeDelegate() {}

    virtual void setEditorData(QWidget *editor, const QModelIndex &index, bool tryDisplay = false) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    std::vector<std::pair<int, QString> > values;
};// class IdTypeDelegate

#endif  // REFIDTYPEDELEGATE_HPP
