#include "deployprojectdialog.h"
#include "ui_deployprojectdialog.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"

DeployProjectDialog::DeployProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeployProjectDialog)
{
    /* configure widgets */
    ui->setupUi(this);
    retranslateUI();

	ui->tvProjects->header()->setResizeMode(0, QHeaderView::Stretch);
	ui->tvProjects->header()->setMovable(false);

	ui->btnOk->setEnabled(false);
	ui->btnOk->setDisabled(true);
	ui->btnOk->updatesEnabled();
	
	/* configure signals */
	connect(ui->cbCompatibleProjectTypes, SIGNAL(currentIndexChanged(int)), this, SLOT(onProjectTypeChanged(int)));
	connect(ui->tvProjects, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(onCheckProject(QTreeWidgetItem*,int)));
}

DeployProjectDialog::~DeployProjectDialog()
{
    delete ui;
}

void DeployProjectDialog::retranslateUI()
{
	setWindowTitle(trUtf8("Publish project(s)..."));
}

QString DeployProjectDialog::selectedProjectType() const
{
	return ui->cbCompatibleProjectTypes->itemData(ui->cbCompatibleProjectTypes->currentIndex(), Qt::UserRole).toString();
}

QStringList DeployProjectDialog::selectedProjects() const
{
	return checkedProjects;
}

void DeployProjectDialog::setProjectTypes(const QStringList compatibleProjects)
{
	ui->cbCompatibleProjectTypes->clear();

	foreach (QString projectType, compatibleProjects)
	{
		if (PluginManager::instance()->projects().keys().contains(projectType))
		{
			IProject * project = qobject_cast<IProject*>(PluginManager::instance()->projects().value(projectType));

			QString projectName = project->pluginFileName().split(".").at(0).section("lib", -1);
			//QString projectLangFile = projectName + QString(".") + SettingsManager::instance()->value("language").toString() + ".qm";
			//QDir languagesDir = QDir(SettingsManager::instance()->value("languagesDir").toString());

			//QString languageName;
			//QDir appDir = QDir(QApplication::applicationDirPath());
			//if (appDir.isRelativePath(SettingsManager::instance()->value("languagesDir").toString()))
			//	languageName = appDir.absoluteFilePath(SettingsManager::instance()->value("languagesDir").toString() + QDir::separator() + projectLangFile);
			//else
			//	languageName = QDir(SettingsManager::instance()->value("languagesDir").toString()).absoluteFilePath(projectLangFile);

			//QTranslator translator;
			//translator.load(languageName);
			//QApplication::installTranslator(&translator);
			ui->cbCompatibleProjectTypes->addItem(project->pluginDisplayName(), QVariant::fromValue(projectType));
			//QApplication::removeTranslator(&translator);
		}
	}

	ui->gbProjectType->setVisible(compatibleProjects.count() > 1);
	ui->gbProjectsList->setEnabled(ui->cbCompatibleProjectTypes->count() > 0);
	ui->gbProjectsList->setDisabled(ui->cbCompatibleProjectTypes->count() == 0);
	ui->gbProjectsList->updatesEnabled();
}

void DeployProjectDialog::insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList)
{
	if (nodeList.keys().contains(nodeData->getProjectId()))
		return ;

	QTreeWidgetItem *item = new QTreeWidgetItem();

	item->setFlags(Qt::ItemIsEnabled);
	if (nodeData->getProjectType().compare(selectedProjectType()) == 0)
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

void DeployProjectDialog::onProjectTypeChanged(int index)
{
	Q_UNUSED(index);
	ui->tvProjects->clear();

	QList<IProjectDescription *> projectsInWorkspace = Workspace::getInstance()->getProjects();
	QHash<QString, QTreeWidgetItem*> projectsNodeList;

	while (!projectsInWorkspace.isEmpty())
	{
		IProjectDescription * projectInfo = projectsInWorkspace.at(0);
		if (projectInfo->getProjectType().compare(selectedProjectType()) == 0)
			insertTreeNode(projectInfo, projectsInWorkspace, projectsNodeList);
		else
			projectsInWorkspace.removeAll(projectInfo);
	}

	ui->tvProjects->expandAll();
	checkedProjects.clear();

	ui->btnOk->setEnabled(false);
	ui->btnOk->setDisabled(true);
	ui->btnOk->updatesEnabled();
}

void DeployProjectDialog::onCheckProject(QTreeWidgetItem * item, int column)
{
	Q_UNUSED(column);
	QString data = item->data(0, Qt::UserRole).toString();

	if (item->checkState(0) == Qt::Checked && !checkedProjects.contains(data))
		checkedProjects.append(data);
	else if (checkedProjects.contains(data))
		checkedProjects.removeAll(data);

	ui->btnOk->setEnabled(checkedProjects.count() > 0);
	ui->btnOk->setDisabled(checkedProjects.count() == 0);
	ui->btnOk->updatesEnabled();
}
