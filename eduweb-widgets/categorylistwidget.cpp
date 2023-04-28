#include <QMessageBox>
#include <QHeaderView>
#include <QFrame>
#include <QSizePolicy>
#include "categorylistwidget.h"

CategoryListWidget::CategoryListWidget(QWidget *parent)
	: QTreeWidget(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(ScrollPerPixel);
    setEditTriggers(NoEditTriggers);
    setDropIndicatorShown(false);
    setIndentation(0);
    setFocusPolicy(Qt::NoFocus);
    setRootIsDecorated(false);
    setUniformRowHeights(false);
    setAnimated(false);
    setExpandsOnDoubleClick(false);
    setHeaderHidden(true);
    setFocusPolicy(Qt::NoFocus);
}

void CategoryListWidget::addCategory(QString category)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QFont font = this->font();
    font.setBold(true);
    item->setFont(0, font);
    item->setBackgroundColor(0, palette().window().color());
    item->setText(0, category);
    item->setTextAlignment(0, Qt::AlignHCenter | Qt::AlignVCenter);
    item->setData(0, Qt::UserRole, QVariant::fromValue(category));
    item->setFlags(Qt::ItemIsEnabled);
    item->setSizeHint(0, QSize(-1, 20));
    addTopLevelItem(item);

    QTreeWidgetItem* childItem = new QTreeWidgetItem();
    childItem->setFlags(Qt::ItemIsEnabled);
    item->addChild(childItem);

    setItemWidget(childItem, 0, createChildWidget());
    item->setExpanded(true);
}

QTreeWidgetItem* CategoryListWidget::addItem(QString category)
{
    QList<QTreeWidgetItem*> topItems = findItems(category, Qt::MatchFixedString, 0);
    if (topItems.isEmpty())
        addCategory(category);

    QTreeWidgetItem* categoryItem = ((QTreeWidgetItem*) findItems(category, Qt::MatchFixedString, 0).first())->child(0);
    QTreeWidget* childWidget = (QTreeWidget*) itemWidget(categoryItem, 0);
    if (!childWidget)
        return NULL;

    QTreeWidgetItem* newItem = new QTreeWidgetItem();
    childWidget->addTopLevelItem(newItem);

    childWidget->doItemsLayout();
    childWidget->setFixedHeight(childWidget->topLevelItemCount() * childWidget->sizeHintForRow(0));
    doItemsLayout();

    return newItem;
}

QTreeWidget* CategoryListWidget::createChildWidget()
{
    QTreeWidget* childWidget = new QTreeWidget();
    childWidget->setRootIsDecorated(false);
    childWidget->setFocusPolicy(Qt::NoFocus);
    childWidget->setFrameStyle(QFrame::NoFrame);
    childWidget->setUniformRowHeights(false);
    childWidget->setHeaderHidden(true);
    childWidget->setColumnCount(2);
    childWidget->setIconSize(QSize(48, 48));
    childWidget->setAnimated(false);
    childWidget->header()->setStretchLastSection(false);
    childWidget->header()->setResizeMode(0, QHeaderView::Stretch);
    childWidget->header()->setResizeMode(1, QHeaderView::Fixed);
    childWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    childWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    childWidget->setVerticalScrollMode(QTreeWidget::ScrollPerPixel);
    childWidget->setAutoFillBackground(true);
    childWidget->setSortingEnabled(true);
    childWidget->sortItems(0, Qt::AscendingOrder);

    childWidget->setStyleSheet(""
        "QTreeView {show-decoration-selected: 1;}"
        "QTreeView::item {padding:14px 10px; padding-top:17px; height:25px; border: 1px solid palette(base);}"
        "QTreeView::text {margin: 0px; padding:0px; subcontrol-origin: border; subcontrol-position: bottom center; border: none;}"
        "QTreeView::item:selected:active,QTreeView::item:selected:!active {border: 1px solid palette(highlight); background-color: palette(highlight); color: palette(highlighted-text);}"
        "QTreeView::item:hover {border: 1px groove palette(dark); background-color: palette(mid); color: palette(highlighted-text);}"
        "QTreeView::item:selected:first,QTreeView::item:hover:first{border-left: none; border-right: none;}"
        "QTreeView::item:selected:last,QTreeView::item:hover:last{border-left: none;}"
        "QTreeView::branch {border:none; image:none; background-color:palette(base); margin:0px; padding-top:2px;}"
        "QTreeView::branch:selected:active,QTreeView::branch:selected:!active {background-color: palette(highlight); border-right: none;}"
        "QTreeView::branch:hover {border: none; background-color: palette(mid); color: palette(highlighted-text); border-right: none;}"
        "QTreeView::branch:has-children:!has-siblings:closed,QTreeView::branch:closed:has-children:has-siblings {image: url(:/treeview/expand.png);}"
        "QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:open:has-children:has-siblings {image: url(:/treeview/collapse.png);}"
    );

    connect(childWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(itemClicked(QTreeWidgetItem*,int)));
    connect(childWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(itemDoubleClicked(QTreeWidgetItem*,int)));

    return childWidget;
}

void CategoryListWidget::itemClicked(QTreeWidgetItem * item, int column)
{
    for(int index = 0; index < topLevelItemCount(); index++)
    {
        QTreeWidgetItem* topItem = topLevelItem(index);
        if (topItem->childCount() > 0)
        {
            QTreeWidget* widget = (QTreeWidget*) itemWidget(topItem->child(0), 0);
            if (item->treeWidget() != widget)
                widget->clearSelection();
        }
    }
}

void CategoryListWidget::itemDoubleClicked(QTreeWidgetItem * item, int column)
{
    emit onDblClickItem(item, column);
}
