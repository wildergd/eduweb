#include "manualsortablelistwidget.h"

ManualSortableListWidget::ManualSortableListWidget(QWidget *parent)
	: QListWidget(parent)
{
	setDragDropMode(QAbstractItemView::InternalMove);
    setDefaultDropAction(Qt::MoveAction);
}

void ManualSortableListWidget::dropEvent(QDropEvent * event)
{
	QListWidget::dropEvent(event);
	emit itemsOrderChanged();
}
