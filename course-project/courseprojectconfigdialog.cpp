#include <QMessageBox>
#include <QByteArray>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include "courseprojectconfigdialog.h"
#include "ui_courseprojectconfigdialog.h"

CourseProjectConfigDialog::CourseProjectConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseProjectConfigDialog)
{
    /* configure widgets */
    ui->setupUi(this);

    /* configure event handlers */
    connect(ui->btnAddProgrammeField, SIGNAL(clicked()), this, SLOT(onAddProgrammeField()));
    connect(ui->btnDeleteProgrammeField, SIGNAL(clicked()), this, SLOT(onRemoveProgrammeField()));
    connect(ui->btnRestoreDefaultProgrammeFields, SIGNAL(clicked()), this, SLOT(onRestoreProgrammeFields()));
    connect(ui->btnAddTopicDesignField, SIGNAL(clicked()), this, SLOT(onAddTopicDesignField()));
    connect(ui->btnDeleteTopicDesignField, SIGNAL(clicked()), this, SLOT(onRemoveTopicDesignField()));
    connect(ui->btnRestoreTopicDesignFields, SIGNAL(clicked()), this, SLOT(onRestoreTopicDesignFields()));
    connect(ui->btnAddLectureDesignField, SIGNAL(clicked()), this, SLOT(onAddLectureDesignField()));
    connect(ui->btnDeleteLectureDesignField, SIGNAL(clicked()), this, SLOT(onRemoveLectureDesignField()));
    connect(ui->btnRestoreLectureDesignFields, SIGNAL(clicked()), this, SLOT(onRestoreLectureDesignFields()));
    connect(ui->btnAddResourceCategory, SIGNAL(clicked()), this, SLOT(onAddResourceCategory()));
    connect(ui->btnDeleteResourceCategory, SIGNAL(clicked()), this, SLOT(onRemoveResourceCategory()));
    connect(ui->btnRestoreResourceCategories, SIGNAL(clicked()), this, SLOT(onRestoreResourcesCategories()));

    connect(ui->lvProgrammeFields, SIGNAL(currentRowChanged(int)), this, SLOT(onProgrammeFieldsSelectionChanged(int)));
    connect(ui->lvTopicDesignFields, SIGNAL(currentRowChanged(int)), this, SLOT(onTopicDesignFieldsSelectionChanged(int)));
    connect(ui->lvLectureDesignFields, SIGNAL(currentRowChanged(int)), this, SLOT(onLectureDesignFieldsSelectionChanged(int)));
    connect(ui->lvResourcesCategories, SIGNAL(currentRowChanged(int)), this, SLOT(onResourcesCategoriesSelectionChanged(int)));
}

CourseProjectConfigDialog::~CourseProjectConfigDialog()
{
    delete ui;
}

void CourseProjectConfigDialog::init(SettingsManager* settings)
{
    QString metadata = QString::fromUtf8(QByteArray::fromBase64(settings->value("CourseProject/courseProgrammeDefaultFields").toString().toAscii()).data());
    if (!metadata.isEmpty())
    {
        foreach(QString field, metadata.split(", "))
            addItemToListWidget(field, ui->lvProgrammeFields);
    }
    else
    {
        loadDefaultMetadata(":/defaults/default-programme-metadata.txt", ui->lvProgrammeFields);
        metadata = QString::fromAscii(programmeMetadata().join(", ").toUtf8().toBase64().data());
        settings->setValue("CourseProject/courseProgrammeDefaultFields", QVariant::fromValue(metadata));
    }
    ui->lvProgrammeFields->clearSelection();

    metadata = QString::fromUtf8(QByteArray::fromBase64(settings->value("CourseProject/courseTopicDesignFields").toString().toAscii()).data());
    if (!metadata.isEmpty())
    {
        foreach(QString field, metadata.split(", "))
            addItemToListWidget(field, ui->lvTopicDesignFields);
    }
    else
    {
        loadDefaultMetadata(":/defaults/default-topic-metadata.txt", ui->lvTopicDesignFields);
        metadata = QString::fromAscii(topicMetadata().join(", ").toUtf8().toBase64().data());
        settings->setValue("CourseProject/courseTopicDesignFields", QVariant::fromValue(metadata));
    }
    ui->lvTopicDesignFields->clearSelection();

    metadata = QString::fromUtf8(QByteArray::fromBase64(settings->value("CourseProject/courseLectureDesignFields").toString().toAscii()).data());
    if (!metadata.isEmpty())
    {
        foreach(QString field, metadata.split(", "))
            addItemToListWidget(field, ui->lvLectureDesignFields);
    }
    else
    {
        loadDefaultMetadata(":/defaults/default-lecture-metadata.txt", ui->lvLectureDesignFields);
        metadata = QString::fromAscii(lectureMetadata().join(", ").toUtf8().toBase64().data());
        settings->setValue("CourseProject/courseLectureDesignFields", QVariant::fromValue(metadata));
    }
    ui->lvLectureDesignFields->clearSelection();

    metadata = QString::fromUtf8(QByteArray::fromBase64(settings->value("CourseProject/courseResourcesCategories").toString().toAscii()).data());
    if (!metadata.isEmpty())
    {
        foreach(QString field, metadata.split(", "))
            addItemToListWidget(field, ui->lvResourcesCategories);
    }
    else
    {
        loadDefaultMetadata(":/defaults/default-resources-categories.txt", ui->lvResourcesCategories);
        metadata = QString::fromAscii(resourcesCategories().join(", ").toUtf8().toBase64().data());
        settings->setValue("CourseProject/courseResourcesCategories", QVariant::fromValue(metadata));
    }
    ui->lvResourcesCategories->clearSelection();
}

QListWidgetItem* CourseProjectConfigDialog::addItemToListWidget(QString text, QListWidget* list)
{
    QListWidgetItem * item = new QListWidgetItem();
    item->setText(text);
    item->setFont(list->font());
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable|Qt::ItemIsDragEnabled);
    list->addItem(item);

    return item;
}

void CourseProjectConfigDialog::loadDefaultMetadata(QString fileName, QListWidget* list)
{
    list->clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("UTF-8"));

    QStringList metadata = in.readAll().split("\n", QString::SkipEmptyParts);
    foreach(QString field, metadata)
        addItemToListWidget(field, list);

    list->clearSelection();
    list->clearFocus();
}

QStringList CourseProjectConfigDialog::programmeMetadata() const
{
    QStringList fields;
    for(int row = 0; row < ui->lvProgrammeFields->count(); row++)
        fields << ui->lvProgrammeFields->item(row)->text();

    return fields;
}

QStringList CourseProjectConfigDialog::topicMetadata() const
{
    QStringList fields;
    for(int row = 0; row < ui->lvTopicDesignFields->count(); row++)
        fields << ui->lvTopicDesignFields->item(row)->text();

    return fields;
}

QStringList CourseProjectConfigDialog::lectureMetadata() const
{
    QStringList fields;
    for(int row = 0; row < ui->lvLectureDesignFields->count(); row++)
        fields << ui->lvLectureDesignFields->item(row)->text();

    return fields;
}

QStringList CourseProjectConfigDialog::resourcesCategories() const
{
    QStringList fields;
    for(int row = 0; row < ui->lvResourcesCategories->count(); row++)
        fields << ui->lvResourcesCategories->item(row)->text();

    return fields;
}

void CourseProjectConfigDialog::enableWidget(QWidget* widget, bool enabled)
{
    widget->setEnabled(enabled);
    widget->setDisabled(!enabled);
    widget->updatesEnabled();
}

void CourseProjectConfigDialog::onAddProgrammeField()
{
    QListWidgetItem* item = addItemToListWidget(trUtf8("Type the name of the field..."), ui->lvProgrammeFields);
    ui->lvProgrammeFields->setCurrentItem(item);
    ui->lvProgrammeFields->editItem(item);
    enableWidget(ui->btnDeleteProgrammeField, true);
}

void CourseProjectConfigDialog::onRemoveProgrammeField()
{
    int itemIndex = ui->lvProgrammeFields->currentRow();

    QListWidgetItem * itemWidget = ui->lvProgrammeFields->takeItem(itemIndex);
    delete itemWidget;
}

void CourseProjectConfigDialog::onRestoreProgrammeFields()
{
    loadDefaultMetadata(":/defaults/default-programme-metadata.txt", ui->lvProgrammeFields);
}

void CourseProjectConfigDialog::onAddTopicDesignField()
{
    QListWidgetItem* item = addItemToListWidget(trUtf8("Type the name of the field..."), ui->lvTopicDesignFields);
    ui->lvTopicDesignFields->setCurrentItem(item);
    ui->lvTopicDesignFields->editItem(item);
    enableWidget(ui->btnDeleteTopicDesignField, true);
}

void CourseProjectConfigDialog::onRemoveTopicDesignField()
{
    int itemIndex = ui->lvTopicDesignFields->currentRow();

    QListWidgetItem * itemWidget = ui->lvTopicDesignFields->takeItem(itemIndex);
    delete itemWidget;
}

void CourseProjectConfigDialog::onRestoreTopicDesignFields()
{
    loadDefaultMetadata(":/defaults/default-topic-metadata.txt", ui->lvTopicDesignFields);
}

void CourseProjectConfigDialog::onAddLectureDesignField()
{
    QListWidgetItem* item = addItemToListWidget(trUtf8("Type the name of the field..."), ui->lvLectureDesignFields);
    ui->lvLectureDesignFields->setCurrentItem(item);
    ui->lvLectureDesignFields->editItem(item);
    enableWidget(ui->btnDeleteLectureDesignField, true);
}

void CourseProjectConfigDialog::onRemoveLectureDesignField()
{
    int itemIndex = ui->lvLectureDesignFields->currentRow();

    QListWidgetItem * itemWidget = ui->lvLectureDesignFields->takeItem(itemIndex);
    delete itemWidget;
}

void CourseProjectConfigDialog::onRestoreLectureDesignFields()
{
    loadDefaultMetadata(":/defaults/default-lecture-metadata.txt", ui->lvLectureDesignFields);
}

void CourseProjectConfigDialog::onAddResourceCategory()
{
    QListWidgetItem* item = addItemToListWidget(trUtf8("Type the name of the category..."), ui->lvResourcesCategories);
    ui->lvResourcesCategories->setCurrentItem(item);
    ui->lvResourcesCategories->editItem(item);
    enableWidget(ui->btnDeleteResourceCategory, true);
}

void CourseProjectConfigDialog::onRemoveResourceCategory()
{
    int itemIndex = ui->lvResourcesCategories->currentRow();

    QListWidgetItem * itemWidget = ui->lvResourcesCategories->takeItem(itemIndex);
    delete itemWidget;
}

void CourseProjectConfigDialog::onRestoreResourcesCategories()
{
    loadDefaultMetadata(":/defaults/default-resources-categories.txt", ui->lvResourcesCategories);
}

void CourseProjectConfigDialog::onProgrammeFieldsSelectionChanged(int currentRow)
{
    enableWidget(ui->btnDeleteProgrammeField, currentRow != -1);
}

void CourseProjectConfigDialog::onTopicDesignFieldsSelectionChanged(int currentRow)
{
    enableWidget(ui->btnDeleteTopicDesignField, currentRow != -1);
}

void CourseProjectConfigDialog::onLectureDesignFieldsSelectionChanged(int currentRow)
{
    enableWidget(ui->btnDeleteLectureDesignField, currentRow != -1);
}

void CourseProjectConfigDialog::onResourcesCategoriesSelectionChanged(int currentRow)
{
    enableWidget(ui->btnDeleteResourceCategory, currentRow != -1);
}

