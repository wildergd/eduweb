#include "exportprojectsdialog.h"
#include "ui_exportprojectsdialog.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"

ExportProjectsDialog::ExportProjectsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportProjectsDialog)
{
    ui->setupUi(this);
	retranslateUI();

    /* configure widgets */
	ui->projects->clear();
	QList<IProjectDescription *> projectsInWorkspace = Workspace::getInstance()->getProjects();
	QHash<QString, QTreeWidgetItem*> projectsNodeList;

	while (!projectsInWorkspace.isEmpty())
	{
		IProjectDescription * projectInfo = projectsInWorkspace.at(0);
		insertTreeNode(projectInfo, projectsInWorkspace, projectsNodeList);
	}

	ui->projects->expandAll();

	checkedProjects.clear();

	/* configure signals */
	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui->projects, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(onCheckProject(QTreeWidgetItem*,int)));
	connect(ui->outputFolder, SIGNAL(folderChanged()), this, SLOT(onOuputFolderChanged()));
}

ExportProjectsDialog::~ExportProjectsDialog()
{
    delete ui;
}

void ExportProjectsDialog::retranslateUI()
{
	ui->retranslateUi(this);
}

QStringList ExportProjectsDialog::selectedProjects() const
{
	return checkedProjects;
}

QString ExportProjectsDialog::exportFolder() const
{
	return ui->outputFolder->folder();
}

void ExportProjectsDialog::insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList)
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

	IPlugin* plugin = PluginManager::instance()->plugins().value(nodeData->getProjectType());
	item->setIcon(0, QIcon(QPixmap(plugin->pluginIcon()).scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

	if (nodeData->referencingProjects().isEmpty())
	{
		ui->projects->addTopLevelItem(item);
	}
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

void ExportProjectsDialog::onCheckProject(QTreeWidgetItem * item, int column)
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

	ui->btnOk->setEnabled(checkedProjects.count() > 0 && !ui->outputFolder->folder().isEmpty());
	ui->btnOk->setDisabled(checkedProjects.count() == 0 || ui->outputFolder->folder().isEmpty());
	ui->btnOk->updatesEnabled();

	if (item->childCount() == 0)
		return ;

	for(int index = 0; index < item->childCount(); index++)
	{
		QTreeWidgetItem* child = item->child(index);
		child->setCheckState(0, item->checkState(0));
	}
}

void ExportProjectsDialog::onOuputFolderChanged()
{
	ui->btnOk->setEnabled(checkedProjects.count() > 0 && !ui->outputFolder->folder().isEmpty());
	ui->btnOk->setDisabled(checkedProjects.count() == 0 || ui->outputFolder->folder().isEmpty());
	ui->btnOk->updatesEnabled();
}
