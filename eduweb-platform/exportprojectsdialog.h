#ifndef EXPORTPROJECTSDIALOG_H
#define EXPORTPROJECTSDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "iprojectdescription.h"

namespace Ui {
    class ExportProjectsDialog;
}

class ExportProjectsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ExportProjectsDialog(QWidget *parent = 0);
    ~ExportProjectsDialog();
	void retranslateUI();

	QStringList selectedProjects() const;
	QString exportFolder() const;

private:
    Ui::ExportProjectsDialog *ui;

	QStringList checkedProjects;
	void insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList);

private slots:
	void onCheckProject(QTreeWidgetItem * item, int column);
	void onOuputFolderChanged();
};

#endif // EXPORTPROJECTSDIALOG_H
