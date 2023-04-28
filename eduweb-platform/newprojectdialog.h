#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "iprojectdescription.h"

namespace Ui {
    class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewProjectDialog(QWidget *parent = 0);
    ~NewProjectDialog();
    void retranslateUI();

	QString title() const;
	bool cloneExisting() const;
	bool isLinked() const;
	QString source() const;
	void setProjectType(const QString compatibleProject);
	QString linkingProject() const;

private:
    Ui::NewProjectDialog *ui;

	QString projectType;
	QTreeWidgetItem* checkedItem;
	QString checkedProject;

	void updateRefenceableProjects();
	void updateLinkableProjects();
	void insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList);

private slots:
	void onEditTitle(const QString & text);
	void onItemChanged(QTreeWidgetItem * item, int column);
	void onToggleLinkToProject(bool on);
};

#endif // NEWPROJECTDIALOG_H
