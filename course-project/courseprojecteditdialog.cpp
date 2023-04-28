#include <QMessageBox>
#include <QByteArray>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QListWidgetItem>
#include "courseprojecteditdialog.h"
#include "ui_courseprojecteditdialog.h"
#include "coursemanageresourcescategoriesdialog.h"

CourseProjectEditDialog::CourseProjectEditDialog(Course* course, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseProjectEditDialog)
{
    /* configure widgets */
    ui->setupUi(this);

    /* initialize data */
    this->course = course;
    ui->edCourseTitle->setText(course->name());

    // course programme
    updateMetadataList(course->programme(), ui->lvProgrammeProperties);

    // resources categories
    updateResourcesCategories(course->resourcesCategories());

    /* configure events */
    connect(ui->btnManageCategories, SIGNAL(clicked()), this, SLOT(onManageResourcesCategories()));
}

CourseProjectEditDialog::~CourseProjectEditDialog()
{
    delete ui;
}

void CourseProjectEditDialog::updateMetadataList(Metadata& metadata, QListWidget* list)
{
    list->clear();

    foreach (Metadata::Field* field, metadata.fields())
    {
        QListWidgetItem * item = new QListWidgetItem();
        item->setText(field->title);
        item->setCheckState((field->isVisible) ? Qt::Checked : Qt::Unchecked);
        item->setFont(list->font());
        Qt::ItemFlags flags = (field->isRemovable) ? Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled|Qt::ItemIsEditable : Qt::ItemIsSelectable|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsDragEnabled;
        item->setFlags(flags);
        item->setData(Qt::UserRole, QVariant::fromValue(field->id));
        list->insertItem(field->order, item);
    }

    list->clearSelection();
}

void CourseProjectEditDialog::updateResourcesCategories(QHash<int, Resource::Category*> resourcesCategoriesList)
{
    QStringList list;

    ui->cbResourceCategory->clear();
    ui->cbResourceCategory->addItem("", QVariant::fromValue(-1));
    for (int index = 0; index < resourcesCategoriesList.count(); index++)
    {
        Resource::Category* category = resourcesCategoriesList.value(index);
        ui->cbResourceCategory->addItem(category->name, QVariant::fromValue(category->id));
        list << QString::number(category->order) + " - " + category->name;
    }

    QMessageBox::about(NULL, "", list.join("\n"));
}

void CourseProjectEditDialog::onManageResourcesCategories()
{
    CourseManageResourcesCategoriesDialog dlgManageCategories;
    dlgManageCategories.init(course->resourcesCategories());
    dlgManageCategories.exec();
    if (dlgManageCategories.result() == QDialog::Accepted)
    {
        foreach(Resource::Category category, dlgManageCategories.categories())
        {
            Resource::Category* existingCategory = course->getResourceCategory(category.id);
            if (!existingCategory)
                existingCategory = course->addResourceCategory();

            existingCategory->name = category.name;
            existingCategory->order = category.order;
        }

        updateResourcesCategories(course->resourcesCategories());
    }
}
