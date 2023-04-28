#ifndef DEPLOYPROJECTSPAGE_H
#define DEPLOYPROJECTSPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include "mainformpage.h"
#include "iprojectdescription.h"
#include "itemconfigbutton.h"

namespace Ui {
    class DeployProjectsPage;
}

class DeployProjectsPage : public MainFormPage
{
    Q_OBJECT

public:
    explicit DeployProjectsPage(QWidget *parent = 0);
    ~DeployProjectsPage();
    void updateContents();
    void retranslateUI();

public slots:
//	void onDeployProjectSelect(QListWidgetItem *current);
    void onDeployProjectSelect(QTreeWidgetItem* item, int column);
	void addProjectBranchToList(QString projectId, QList<IProjectDescription*> & projectsList);
    void onConfigButtonClick(ItemConfigButton* button);
	
protected:
    void showEvent(QShowEvent * event);

private:
    Ui::DeployProjectsPage *ui;
};

#endif // DEPLOYPROJECTSPAGE_H
