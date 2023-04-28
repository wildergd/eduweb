#ifndef COURSEPROJECTEDITDIALOG_H
#define COURSEPROJECTEDITDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "course.h"

namespace Ui {
    class CourseProjectEditDialog;
}

class CourseProjectEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseProjectEditDialog(Course* course, QWidget *parent = 0);
    ~CourseProjectEditDialog();

private:
    Ui::CourseProjectEditDialog *ui;
    Course* course;

    void updateMetadataList(Metadata& metadata, QListWidget* list);
    void updateResourcesCategories(QHash<int, Resource::Category*> resourcesCategoriesList);

private slots:
    /* course programme */

    /* course topics */

    /* course lectures */

    /* course resources */
    void onManageResourcesCategories();
};

#endif // COURSEPROJECTEDITDIALOG_H
