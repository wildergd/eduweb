#ifndef SYNCPROJECTSDIALOG_H
#define SYNCPROJECTSDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "iprojectdescription.h"

namespace Ui {
    class SyncProjectsDialog;
}

class SyncProjectsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SyncProjectsDialog(QWidget *parent = 0);
    ~SyncProjectsDialog();

	QStringList selectedProjects() const;
	QString sourceFolder() const;

private:
    Ui::SyncProjectsDialog *ui;

	QStringList checkedProjects;
	void retranslateUI();
	void insertTreeNode(IProjectDescription* nodeData, QHash<QString, IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList);
	void setFolder(const QString folder);

private slots:
	void onCheckProject(QTreeWidgetItem * item, int column);
	void onSourceFolderChanged();
};

#endif // SYNCPROJECTSDIALOG_H
