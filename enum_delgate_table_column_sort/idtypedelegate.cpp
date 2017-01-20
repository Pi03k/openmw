#include "idtypedelegate.hpp"
#include "universalid.hpp"

IdTypeDelegate::IdTypeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    for (int i = 0; i < UniversalId::NumberOfTypes; ++i)
    {
        UniversalId id(static_cast<UniversalId::Type>(i));
        values.push_back(std::make_pair (id.getType(), QString::fromUtf8(id.getTypeName().c_str())));
    }
}

void IdTypeDelegate::setEditorData(QWidget *editor, const QModelIndex &index, bool tryDisplay) const
{
}

void IdTypeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}

QSize IdTypeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
}
