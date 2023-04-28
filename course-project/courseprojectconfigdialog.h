#ifndef COURSEPROJECTCONFIGDIALOG_H
#define COURSEPROJECTCONFIGDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include "settingsmanager.h"
#include "metadata.h"

namespace Ui {
    class CourseProjectConfigDialog;
}

class CourseProjectConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseProjectConfigDialog(QWidget *parent = 0);
    ~CourseProjectConfigDialog();

    QStringList programmeMetadata() const;
    QStringList topicMetadata() const;
    QStringList lectureMetadata() const;
    QStringList resourcesCategories() const;

    void enableWidget(QWidget* widget, bool enabled);
    void init(SettingsManager* settings);

private slots:
    void onAddProgrammeField();
    void onRemoveProgrammeField();
    void onRestoreProgrammeFields();
    void onAddTopicDesignField();
    void onRemoveTopicDesignField();
    void onRestoreTopicDesignFields();
    void onAddLectureDesignField();
    void onRemoveLectureDesignField();
    void onRestoreLectureDesignFields();
    void onAddResourceCategory();
    void onRemoveResourceCategory();
    void onRestoreResourcesCategories();

    void onProgrammeFieldsSelectionChanged(int currentRow);
    void onTopicDesignFieldsSelectionChanged(int currentRow);
    void onLectureDesignFieldsSelectionChanged(int currentRow);
    void onResourcesCategoriesSelectionChanged(int currentRow);

private:
    Ui::CourseProjectConfigDialog *ui;

    QListWidgetItem* addItemToListWidget(QString text, QListWidget* list);
    void loadDefaultMetadata(QString fileName, QListWidget* list);
};

#endif // COURSEPROJECTCONFIGDIALOG_H
