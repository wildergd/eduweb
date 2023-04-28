#ifndef NEWPROJECTPAGE_H
#define NEWPROJECTPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include "mainformpage.h"
#include "itemconfigbutton.h"

namespace Ui {
    class NewProjectPage;
}

class NewProjectPage : public MainFormPage
{
    Q_OBJECT

public:
    explicit NewProjectPage(QWidget *parent = 0);
    ~NewProjectPage();
    void updateContents();
    void retranslateUI();

private slots:
    void onAvailableProjectsItemClicked(QListWidgetItem *item);
//    void onNewProjectSelect(QListWidgetItem *current);
    void onNewProjectSelect(QTreeWidgetItem* item, int column);
    void onConfigButtonClick(ItemConfigButton* button);

protected:
    void showEvent(QShowEvent * event);

private:
    Ui::NewProjectPage *ui;
};

#endif // NEWPROJECTPAGE_H
