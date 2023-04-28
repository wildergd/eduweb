#include <QUuid>
#include <QInputDialog>
#include "coursemanageresourcescategoriesdialog.h"
#include "ui_coursemanageresourcescategoriesdialog.h"

CourseManageResourcesCategoriesDialog::CourseManageResourcesCategoriesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseManageResourcesCategoriesDialog)
{
    /* configure widgets */
    ui->setupUi(this);

    /* configure events */
    connect(ui->btnAddResourceCategory, SIGNAL(clicked()), this, SLOT(onAddCategory()));
    connect(ui->btnDeleteResourceCategory, SIGNAL(clicked()), this, SLOT(onRemoveCategory()));
    connect(ui->lvResourcesCategories, SIGNAL(currentRowChanged(int)), this, SLOT(onResourcesCategoriesSelectionChanged(int)));
}

CourseManageResourcesCategoriesDialog::~CourseManageResourcesCategoriesDialog()
{
    delete ui;
}

void CourseManageResourcesCategoriesDialog::enableWidget(QWidget* widget, bool enabled)
{
    widget->setEnabled(enabled);
    widget->setDisabled(!enabled);
    widget->updatesEnabled();
}

void CourseManageResourcesCategoriesDialog::init(QHash<int,Resource::Category*> categories)
{
    ui->lvResourcesCategories->clear();
    for(int index = 0; index < categories.count(); index++)
    {
        Resource::Category* category = categories.value(index);
        QListWidgetItem* item = addItemToListWidget(category->name, ui->lvResourcesCategories);
        item->setData(Qt::UserRole, QVariant::fromValue(category->id));
    }
}

QListWidgetItem* CourseManageResourcesCategoriesDialog::addItemToListWidget(QString text, QListWidget* list)
{
    QListWidgetItem * item = new QListWidgetItem();
    item->setText(text);
    item->setFont(list->font());
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsDragEnabled);
    list->addItem(item);

    return item;
}

QHash<int,Resource::Category> CourseManageResourcesCategoriesDialog::categories()
{
    QHash<int,Resource::Category> resourcesCategoriesList;
    for(int row = 0; row < ui->lvResourcesCategories->count(); row++)
    {
        QListWidgetItem* item = ui->lvResourcesCategories->item(row);
        Resource::Category category;
        category.id = item->data(Qt::UserRole).toString();
        category.name = item->text();
        category.order = row;
        resourcesCategoriesList.insert(category.order, category);
    }

    return resourcesCategoriesList;
}

void CourseManageResourcesCategoriesDialog::onAddCategory()
{
    QInputDialog getCategoryNameDlg;
    getCategoryNameDlg.setWindowTitle(trUtf8("Add new category"));
    getCategoryNameDlg.setLabelText(trUtf8("Enter the name of the category"));
    getCategoryNameDlg.setInputMode(QInputDialog::TextInput);
    getCategoryNameDlg.setOkButtonText(trUtf8("Ok"));
    getCategoryNameDlg.setCancelButtonText(trUtf8("Cancel"));
    getCategoryNameDlg.exec();

    if (getCategoryNameDlg.result() != QDialog::Accepted)
        return ;

    if (getCategoryNameDlg.textValue().isEmpty())
        return ;

    QListWidgetItem* item = addItemToListWidget(getCategoryNameDlg.textValue(), ui->lvResourcesCategories);
    item->setData(Qt::UserRole, QVariant::fromValue(QUuid::createUuid().toString()));
}

void CourseManageResourcesCategoriesDialog::onRemoveCategory()
{
    int itemIndex = ui->lvResourcesCategories->currentRow();
    QListWidgetItem * itemWidget = ui->lvResourcesCategories->takeItem(itemIndex);
    delete itemWidget;
}

void CourseManageResourcesCategoriesDialog::onResourcesCategoriesSelectionChanged(int currentRow)
{
    enableWidget(ui->btnDeleteResourceCategory, currentRow != -1);
}
