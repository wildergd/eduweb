#ifndef MANUALSORTABLELISTWIDGET_H
#define MANUALSORTABLELISTWIDGET_H

#include <QListWidget>
#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
#include <QtDesigner/QDesignerExportWidget>
#endif

#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
class QDESIGNER_WIDGET_EXPORT ManualSortableListWidget: public QListWidget
#else
class ManualSortableListWidget: public QListWidget
#endif
{
	Q_OBJECT
public:
	ManualSortableListWidget(QWidget *parent = 0);

protected:
	void dropEvent(QDropEvent * event);

signals:
	void itemsOrderChanged();

};

#endif
