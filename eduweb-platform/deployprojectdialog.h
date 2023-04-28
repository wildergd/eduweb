#ifndef DEPLOYPROJECTDIALOG_H
#define DEPLOYPROJECTDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "iprojectdescription.h"

namespace Ui {
    class DeployProjectDialog;
}

class DeployProjectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DeployProjectDialog(QWidget *parent = 0);
    ~DeployProjectDialog();
    void retranslateUI();
	QString selectedProjectType() const;
	QStringList selectedProjects() const;
	void setProjectTypes(const QStringList compatibleProjects);
	
private:
	void insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList);
	
private slots:
	void onProjectTypeChanged(int index);
	void onCheckProject(QTreeWidgetItem * item, int column);
	
private:
    Ui::DeployProjectDialog *ui;

	QStringList checkedProjects;
};

#endif // DEPLOYPROJECTDIALOG_H
