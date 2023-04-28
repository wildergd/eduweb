#ifndef LINKPROJECTSDIALOG_H
#define LINKPROJECTSDIALOG_H

#include <QDialog>
#include "iprojectdescription.h"

namespace Ui {
    class LinkProjectsDialog;
}

class LinkProjectsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LinkProjectsDialog(QWidget *parent = 0);
    ~LinkProjectsDialog();

	void retranslateUI();
	void setProject(IProjectDescription* description);
	QStringList linkedProjects() const;
	
private:
    Ui::LinkProjectsDialog *ui;

	void updateReferencedProjects();
	void updateAvailableProjects();
	void checkReferences();

	IProjectDescription* projectInfo;

private slots:
	void onLinkedProjectsListSelectionChanged();
	void onAvailableProjectsListSelectionChanged();
	void onLinkProjectsClicked();
	void onUnlinkProjectsClicked();
};

#endif // LINKPROJECTSDIALOG_H
