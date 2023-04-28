#ifndef COURSEMANAGERESOURCESCATEGORIESDIALOG_H
#define COURSEMANAGERESOURCESCATEGORIESDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QHash>
#include "resource.h"

namespace Ui {
    class CourseManageResourcesCategoriesDialog;
}

class CourseManageResourcesCategoriesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseManageResourcesCategoriesDialog(QWidget *parent = 0);
    ~CourseManageResourcesCategoriesDialog();

    void init(QHash<int, Resource::Category*> categories);
    QHash<int, Resource::Category> categories();

private:
    Ui::CourseManageResourcesCategoriesDialog *ui;
    QListWidgetItem* addItemToListWidget(QString text, QListWidget* list);
    void enableWidget(QWidget* widget, bool enabled);

private slots:
    void onAddCategory();
    void onRemoveCategory();
    void onResourcesCategoriesSelectionChanged(int currentRow);
};

#endif // COURSEMANAGERESOURCESCATEGORIESDIALOG_H
