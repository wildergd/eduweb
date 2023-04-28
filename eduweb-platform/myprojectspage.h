#ifndef MYPROJECTSPAGE_H
#define MYPROJECTSPAGE_H

#include <QWidget>
#include <QHash>
#include <QTreeWidgetItem>
#include "mainformpage.h"
#include "iprojectdescription.h"

namespace Ui {
    class MyProjectsPage;
}

class MyProjectsPage : public MainFormPage
{
    Q_OBJECT

public:
    explicit MyProjectsPage(QWidget *parent = 0);
    ~MyProjectsPage();
    void updateContents();
    void retranslateUI();

public slots:
	void onOpenExistingProject(QTreeWidgetItem * item, int column);
	void onProjectListSelectionChanged();
	void onLinkProjectsClick();
	void onExportProjectsClick();
	void onSyncProjectsClick();
	void onDeleteProjectsClick();

protected:
    void showEvent(QShowEvent * event);

private:
    Ui::MyProjectsPage *ui;
    void insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList);
};

#endif // MYPROJECTSPAGE_H
