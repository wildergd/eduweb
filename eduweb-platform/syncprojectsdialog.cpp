#include "syncprojectsdialog.h"
#include "ui_syncprojectsdialog.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"

SyncProjectsDialog::SyncProjectsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SyncProjectsDialog)
{
    ui->setupUi(this);
	retranslateUI();

	/* configure signals */
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui->projects, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(onCheckProject(QTreeWidgetItem*,int)));
	connect(ui->inputFolder, SIGNAL(folderChanged()), this, SLOT(onSourceFolderChanged()));
}

SyncProjectsDialog::~SyncProjectsDialog()
{
    delete ui;
}

void SyncProjectsDialog::retranslateUI()
{
	ui->retranslateUi(this);
}

void SyncProjectsDialog::setFolder(const QString folder)
{
	ui->projects->clear();
	QHash<QString, IProjectDescription *> projectsInWorkspace = Workspace::getInstance()->scanFolder(folder);
	QHash<QString, QTreeWidgetItem*> projectsNodeList;

	while (!projectsInWorkspace.isEmpty())
	{
		IProjectDescription * projectInfo = projectsInWorkspace.value(projectsInWorkspace.keys().at(0));
		insertTreeNode(projectInfo, projectsInWorkspace, projectsNodeList);
	}
	ui->projects->expandAll();
	checkedProjects.clear();
}


QStringList SyncProjectsDialog::selectedProjects() const
{
	return checkedProjects;
}

QString SyncProjectsDialog::sourceFolder() const
{
	return ui->inputFolder->folder();
}

void SyncProjectsDialog::insertTreeNode(IProjectDescription* nodeData, QHash<QString, IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList)
{
	if (nodeList.keys().contains(nodeData->getProjectId()))
		return ;

	QTreeWidgetItem *item = new QTreeWidgetItem();
	item->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
	item->setCheckState(0, Qt::Unchecked);
	item->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
	item->setData(0, Qt::UserRole, QVariant::fromValue(nodeData->getProjectId()));
	item->setText(0, nodeData->getProjectName());
	item->setText(1, nodeData->getModifiedDate().toString("MMM d, yyyy"));

	if (Workspace::getInstance()->exists(nodeData->getProjectId()))
	{
		item->setForeground(0, QBrush(Qt::red));
		item->setForeground(1, QBrush(Qt::red));
	}

	IPlugin* plugin = PluginManager::instance()->plugins().value(nodeData->getProjectType());
	item->setIcon(0, QIcon(QPixmap(plugin->pluginIcon()).scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

	if (nodeData->referencingProjects().isEmpty())
	{
		ui->projects->addTopLevelItem(item);
	}
	else
	{
		if (projectsList.keys().contains(nodeData->referencingProjects().at(0)))
		{
			IProjectDescription* parentProject = projectsList.value(nodeData->referencingProjects().at(0));
			insertTreeNode(parentProject, projectsList, nodeList);
		}

		if (nodeList.keys().contains(nodeData->referencingProjects().at(0)))
		{
			QTreeWidgetItem * parentItem = nodeList.value(nodeData->referencingProjects().at(0));
			parentItem->addChild(item);
		}
	}

	nodeList.insert(nodeData->getProjectId(), item);
	projectsList.remove(projectsList.key(nodeData));
}

void SyncProjectsDialog::onCheckProject(QTreeWidgetItem * item, int column)
{
	Q_UNUSED(column);

	QString data = item->data(0, Qt::UserRole).toString();
	if (item->checkState(0) == Qt::Checked)
	{
		if (!checkedProjects.contains(data))
			checkedProjects.append(data);
	}
	else
	{
		if (checkedProjects.contains(data))
			checkedProjects.removeAll(data);
	}

	ui->btnOk->setEnabled(checkedProjects.count() > 0 && !ui->inputFolder->folder().isEmpty());
	ui->btnOk->setDisabled(checkedProjects.count() == 0 || ui->inputFolder->folder().isEmpty());
	ui->btnOk->updatesEnabled();

	if (item->childCount() == 0)
		return ;

	for(int index = 0; index < item->childCount(); index++)
	{
		QTreeWidgetItem* child = item->child(index);
		child->setCheckState(0, item->checkState(0));
	}
}

void SyncProjectsDialog::onSourceFolderChanged()
{
	setFolder(ui->inputFolder->folder());

	ui->btnOk->setEnabled(checkedProjects.count() > 0 && !ui->inputFolder->folder().isEmpty());
	ui->btnOk->setDisabled(checkedProjects.count() == 0 || ui->inputFolder->folder().isEmpty());
	ui->btnOk->updatesEnabled();
}
