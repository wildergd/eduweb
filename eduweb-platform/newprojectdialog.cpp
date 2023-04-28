#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"
#include "ireusable.h"
#include "iprojectcanbecontained.h"
#include "iprojectcontainer.h"

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    /* configure widgets */
    ui->setupUi(this);

    ui->chkImportOnlyAsReference->setHidden(true);
	ui->gbSetReferencing->setHidden(true);

    retranslateUI();
    adjustSize();
	
	/* configure signals */
	connect(ui->edTitle, SIGNAL(textChanged(QString)), this, SLOT(onEditTitle(QString)));
	connect(ui->tvProjects, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(onItemChanged(QTreeWidgetItem*,int)));
	connect(ui->gbSetReferencing, SIGNAL(toggled(bool)), this, SLOT(onToggleLinkToProject(bool)));
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::retranslateUI()
{
	setWindowTitle(trUtf8("Create new project..."));
}

QString NewProjectDialog::title() const
{
	return ui->edTitle->text();
}

bool NewProjectDialog::cloneExisting() const
{
	return ui->gbImportFromExisting->isChecked();
}

bool NewProjectDialog::isLinked() const
{
	return ui->gbSetReferencing->isChecked();
}

QString NewProjectDialog::source() const
{
	return ui->cbProjectsList->itemData(ui->cbProjectsList->currentIndex(), Qt::UserRole).toString();
}

void NewProjectDialog::setProjectType(const QString compatibleProject)
{
	projectType = compatibleProject;
	ui->gbImportFromExisting->setHidden(true);
	ui->gbSetReferencing->setHidden(true);

	if (PluginManager::instance()->projects().keys().contains(compatibleProject) && qobject_cast<IReusable*>(PluginManager::instance()->projects().value(compatibleProject)) != 0)
	{
		ui->gbImportFromExisting->setHidden(false);
		updateRefenceableProjects();
	}

	if (PluginManager::instance()->projects().keys().contains(compatibleProject) && qobject_cast<IProjectCanBeContained*>(PluginManager::instance()->projects().value(compatibleProject)) != 0)
	{
		ui->gbSetReferencing->setHidden(false);
		updateLinkableProjects();
	}
}

QString NewProjectDialog::linkingProject() const
{
	return checkedProject;
}

void NewProjectDialog::updateRefenceableProjects()
{
    ui->cbProjectsList->clear();

	if (!ui->gbImportFromExisting->isHidden())
	{
		QList<IProjectDescription *> projectsInWorkspace = Workspace::getInstance()->getProjects();
		foreach (IProjectDescription * projectInfo, projectsInWorkspace)
		{
			if (projectInfo->getProjectType().compare(projectType) == 0)
				ui->cbProjectsList->addItem(projectInfo->getProjectName(), QVariant::fromValue(projectInfo->getProjectId()));
		}
        ui->gbImportFromExisting->setHidden(ui->cbProjectsList->count() == 0);
    }
}

void NewProjectDialog::updateLinkableProjects()
{
	ui->tvProjects->clear();
	if (!ui->gbSetReferencing->isHidden())
	{
		QList<IProjectDescription *> projectsInWorkspace = Workspace::getInstance()->getProjects();
		QHash<QString, QTreeWidgetItem*> projectsNodeList;

		while (!projectsInWorkspace.isEmpty())
		{
			IProjectDescription * projectInfo = projectsInWorkspace.at(0);
			IProjectContainer* container = qobject_cast<IProjectContainer*>(PluginManager::instance()->projects().value(projectInfo->getProjectType()));
			if (container != 0 && container->projectsCanLink().contains(projectType) && projectInfo->getProjectType().compare(projectType) != 0)
				insertTreeNode(projectInfo, projectsInWorkspace, projectsNodeList);
			else
				projectsInWorkspace.removeAll(projectInfo);
		}

        ui->tvProjects->expandAll();
        ui->gbSetReferencing->setHidden(ui->tvProjects->invisibleRootItem()->childCount() == 0);
    }
}

void NewProjectDialog::insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList)
{
	if (nodeList.keys().contains(nodeData->getProjectId()))
		return ;

	QTreeWidgetItem *item = new QTreeWidgetItem();

	item->setFlags(Qt::ItemIsEnabled);

	IProjectContainer* container = qobject_cast<IProjectContainer*>(PluginManager::instance()->projects().value(nodeData->getProjectType()));
	if (container != 0 && container->projectsCanLink().contains(projectType) && nodeData->getProjectType().compare(projectType) != 0)
	{
		item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
		item->setCheckState(0, Qt::Unchecked);
	}

	item->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
	item->setText(0, nodeData->getProjectName());
	item->setData(0, Qt::UserRole, QVariant::fromValue(nodeData->getProjectId()));

	IPlugin* plugin = PluginManager::instance()->plugins().value(nodeData->getProjectType());
	item->setIcon(0, QIcon(QPixmap(plugin->pluginIcon()).scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

	if (nodeData->referencingProjects().isEmpty())
		ui->tvProjects->addTopLevelItem(item);
	else
	{
		IProjectDescription* parentProject = Workspace::getInstance()->getProject(nodeData->referencingProjects().at(0));
		insertTreeNode(parentProject, projectsList, nodeList);
		QTreeWidgetItem * parentItem = nodeList.value(parentProject->getProjectId());
		parentItem->addChild(item);
	}

	nodeList.insert(nodeData->getProjectId(), item);

	projectsList.removeAll(nodeData);
}

void NewProjectDialog::onEditTitle(const QString & text)
{
	ui->btnOk->setDisabled(text.isEmpty());
	ui->btnOk->updatesEnabled();
}

void NewProjectDialog::onItemChanged(QTreeWidgetItem * item, int column)
{
	Q_UNUSED(column);

	QString data = item->data(0, Qt::UserRole).toString();

	if (item->checkState(0) == Qt::Checked)
	{
		if (checkedItem != NULL && checkedItem != item)
			checkedItem->setCheckState(0, Qt::Unchecked);

		checkedItem = item;
		checkedProject = data;
	}
	else
	{
		checkedItem = NULL;
		checkedProject = "";
	}

	ui->btnOk->setDisabled(ui->edTitle->text().isEmpty() || checkedProject.isEmpty());
	ui->btnOk->updatesEnabled();}

void NewProjectDialog::onToggleLinkToProject(bool on)
{
	if (on)
		ui->btnOk->setDisabled(ui->edTitle->text().isEmpty() || checkedProject.isEmpty());
	else
		ui->btnOk->setDisabled(ui->edTitle->text().isEmpty());

	ui->btnOk->updatesEnabled();
}
