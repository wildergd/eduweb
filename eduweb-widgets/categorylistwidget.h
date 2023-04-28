#ifndef CATEGORYLISTWIDGET_H
#define CATEGORYLISTWIDGET_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
#include <QtDesigner/QDesignerExportWidget>
#endif

#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
class QDESIGNER_WIDGET_EXPORT CategoryListWidget: public QTreeWidget
#else
class CategoryListWidget: public QTreeWidget
#endif
{
	Q_OBJECT
public:
	CategoryListWidget(QWidget *parent = 0);
	
    void addCategory(QString category);
	QTreeWidgetItem* addItem(QString category);

private:
    QTreeWidget* createChildWidget();

private slots:
    void itemClicked(QTreeWidgetItem * item, int column);
    void itemDoubleClicked(QTreeWidgetItem * item, int column);

signals:
    void onDblClickItem(QTreeWidgetItem * item, int column);
};

#endif //CATEGORYLISTWIDGET_H
