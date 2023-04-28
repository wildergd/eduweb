#include "linkprojectsdialog.h"
#include "ui_linkprojectsdialog.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"
#include "iprojectcontainer.h"
#include "iprojectcanbecontained.h"

LinkProjectsDialog::LinkProjectsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkProjectsDialog)
{
    ui->setupUi(this);

    /* configure widgets */
	
	/* configure signals */
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui->btnLinkProjects, SIGNAL(clicked()), this, SLOT(onLinkProjectsClicked()));
	connect(ui->btnUnlinkProjects, SIGNAL(clicked()), this, SLOT(onUnlinkProjectsClicked()));
	connect(ui->linkProjects, SIGNAL(itemSelectionChanged()), this, SLOT(onLinkedProjectsListSelectionChanged()));
	connect(ui->availableProjects, SIGNAL(itemSelectionChanged()), this, SLOT(onAvailableProjectsListSelectionChanged()));
}

LinkProjectsDialog::~LinkProjectsDialog()
{
    delete ui;
}

void LinkProjectsDialog::retranslateUI()
{
	ui->retranslateUi(this);
}

void LinkProjectsDialog::updateReferencedProjects()
{
	ui->linkProjects->clear();
	if(projectInfo->referencedProjects().isEmpty())
		return ;

	foreach(QString projectID, projectInfo->referencedProjects())
	{
		IProjectDescription* description = Workspace::getInstance()->getProject(projectID);

		QTreeWidgetItem *item = new QTreeWidgetItem();
		item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		item->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
		item->setData(0, Qt::UserRole, QVariant::fromValue(description->getProjectId()));
		item->setText(0, description->getProjectName());
		item->setText(1, description->getModifiedDate().toString("MMM d, yyyy"));

		IPlugin* plugin = PluginManager::instance()->plugins().value(description->getProjectType());
		item->setIcon(0, QIcon(QPixmap(plugin->pluginIcon()).scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

		ui->linkProjects->addTopLevelItem(item);
	}
}

void LinkProjectsDialog::updateAvailableProjects()
{
	ui->availableProjects->clear();
	QList<IProjectDescription *> projectsInWorkspace = Workspace::getInstance()->getProjects();
	foreach(IProjectDescription* description, projectsInWorkspace)
	{
		if (description->getProjectType().compare(projectInfo->getProjectType()) != 0 && qobject_cast<IProjectCanBeContained*>(PluginManager::instance()->projects().value(description->getProjectType())))
		{
			QTreeWidgetItem *item = new QTreeWidgetItem();
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
			item->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
			item->setData(0, Qt::UserRole, QVariant::fromValue(description->getProjectId()));
			item->setText(0, description->getProjectName());
			item->setText(1, description->getModifiedDate().toString("MMM d, yyyy"));

			IPlugin* plugin = PluginManager::instance()->plugins().value(description->getProjectType());
			item->setIcon(0, QIcon(QPixmap(plugin->pluginIcon()).scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

			if (description->referencingProjects().isEmpty())
				ui->availableProjects->addTopLevelItem(item);
		}
	}
}

QStringList LinkProjectsDialog::linkedProjects() const
{
	QStringList projectsLinked;

	for (int index = 0; index < ui->linkProjects->topLevelItemCount(); index++)
	{
		QTreeWidgetItem* item = ui->linkProjects->topLevelItem(index);	
		QString projectID = item->data(0, Qt::UserRole).toString();
		projectsLinked.append(projectID);
	}

	return projectsLinked;
}

void LinkProjectsDialog::setProject(IProjectDescription* description)
{
	projectInfo = description;
	updateReferencedProjects();
	updateAvailableProjects();
}

void LinkProjectsDialog::checkReferences()
{
	QSet<QString> referencedProjects = projectInfo->referencedProjects().toSet();
	QSet<QString> projectsToBeReferenced = linkedProjects().toSet();
	QSet<QString> allProjects = (referencedProjects - projectsToBeReferenced) + (projectsToBeReferenced - referencedProjects);

	ui->btnOk->setEnabled(!allProjects.isEmpty());
	ui->btnOk->setDisabled(allProjects.isEmpty());
	ui->btnOk->updatesEnabled();
}

void LinkProjectsDialog::onLinkedProjectsListSelectionChanged()
{
	ui->btnUnlinkProjects->setEnabled(ui->linkProjects->selectedItems().count() > 0);
	ui->btnUnlinkProjects->setDisabled(ui->linkProjects->selectedItems().count() == 0);
	ui->btnUnlinkProjects->updatesEnabled();

	ui->availableProjects->clearSelection();
}

void LinkProjectsDialog::onAvailableProjectsListSelectionChanged()
{
	ui->btnLinkProjects->setEnabled(ui->availableProjects->selectedItems().count() > 0);
	ui->btnLinkProjects->setDisabled(ui->availableProjects->selectedItems().count() == 0);
	ui->btnLinkProjects->updatesEnabled();

	ui->linkProjects->clearSelection();
}

void LinkProjectsDialog::onLinkProjectsClicked()
{
	QTreeWidgetItem* item = ui->availableProjects->takeTopLevelItem(ui->availableProjects->currentIndex().row());
	ui->linkProjects->addTopLevelItem(item);
	checkReferences();
}

void LinkProjectsDialog::onUnlinkProjectsClicked()
{
	QTreeWidgetItem* item = ui->linkProjects->takeTopLevelItem(ui->linkProjects->currentIndex().row());
	ui->availableProjects->addTopLevelItem(item);
	checkReferences();
}
