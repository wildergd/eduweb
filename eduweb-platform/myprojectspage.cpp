#include <QMessageBox>
#include "myprojectspage.h"
#include "ui_myprojectspage.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"
#include "iplugin.h"
#include "iprojectdescription.h"
#include "iprojectcontainer.h"
#include "actionprogresswidget.h"
#include "exportprojectsdialog.h"
#include "syncprojectsdialog.h"
#include "linkprojectsdialog.h"
#include "filesystemutils.h"

MyProjectsPage::MyProjectsPage(QWidget *parent) :
    MainFormPage(parent),
    ui(new Ui::MyProjectsPage)
{
    /* configure widgets */
    ui->setupUi(this);

//    ui->projects->header()->setResizeMode(0, QHeaderView::Interactive);
//    ui->projects->header()->setResizeMode(1, QHeaderView::ResizeToContents);
//    ui->projects->header()->resizeSection(0, 460);
    ui->projects->header()->setResizeMode(0, QHeaderView::Stretch);
    ui->projects->header()->setResizeMode(1, QHeaderView::Fixed);
    ui->projects->header()->setMovable(false);
    ui->projects->setAlternatingRowColors(false);
    ui->projects->sortItems(0, Qt::AscendingOrder);
	
    retranslateUI();

    /* configure signals */
    connect(ui->projects, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onOpenExistingProject(QTreeWidgetItem*,int)));
    connect(ui->projects, SIGNAL(itemSelectionChanged()), this, SLOT(onProjectListSelectionChanged()));

    connect(ui->linkProjects, SIGNAL(clicked()), this, SLOT(onLinkProjectsClick()));
	connect(ui->exportProjects, SIGNAL(clicked()), this, SLOT(onExportProjectsClick()));
	connect(ui->syncProjects, SIGNAL(clicked()), this, SLOT(onSyncProjectsClick()));
	connect(ui->deleteProjects, SIGNAL(clicked()), this, SLOT(onDeleteProjectsClick()));
}

MyProjectsPage::~MyProjectsPage()
{
    delete ui;
}

void MyProjectsPage::retranslateUI()
{
    ui->retranslateUi(this);
/*	ui->hint->setText(trUtf8("Doble-click to edit a project"));
    ui->projects->headerItem()->setText(0, trUtf8("Project"));
	ui->projects->headerItem()->setText(1, trUtf8("Modified"));
    ui->exportProjects->setText(trUtf8("Export projects"));
    ui->syncProjects->setText(trUtf8("Update projects"));
    ui->deleteProjects->setText(trUtf8("Remove project(s)")); */
}

void MyProjectsPage::updateContents()
{
    ui->projects->clear();
	QList<IProjectDescription *> projectsInWorkspace = Workspace::getInstance()->getProjects();
	QHash<QString, QTreeWidgetItem*> projectsNodeList;

	while (!projectsInWorkspace.isEmpty())
	{
			IProjectDescription * projectInfo = projectsInWorkspace.at(0);
			insertTreeNode(projectInfo, projectsInWorkspace, projectsNodeList);
	}

    ui->projects->expandAll();
}

void MyProjectsPage::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);
    ui->projects->clearSelection();
}

void MyProjectsPage::insertTreeNode(IProjectDescription* nodeData, QList<IProjectDescription *> & projectsList, QHash<QString, QTreeWidgetItem*> & nodeList)
{
    if (nodeList.keys().contains(nodeData->getProjectId()))
		return ;

	QTreeWidgetItem *item = new QTreeWidgetItem();
	item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
	item->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
	item->setText(0, nodeData->getProjectName());
	item->setText(1, nodeData->getModifiedDate().toString("MMM d, yyyy"));
	item->setData(2, Qt::UserRole, QVariant::fromValue(nodeData->getProjectId()));

	IPlugin* plugin = PluginManager::instance()->plugins().value(nodeData->getProjectType());
	
	if (plugin)
		item->setIcon(0, QIcon(QPixmap(plugin->pluginIcon()).scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
	else
	{
		item->setIcon(0, QIcon(QPixmap(":/icons/unknown_project.png").scaled(18, 18, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
		item->setFlags(Qt::NoItemFlags);
	}

	if (nodeData->referencingProjects().isEmpty())
		ui->projects->addTopLevelItem(item);
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

void MyProjectsPage::onOpenExistingProject(QTreeWidgetItem * item, int column)
{
	Q_UNUSED(column);
	QString projectId = item->data(2, Qt::UserRole).toString();
	IProjectDescription * description = Workspace::getInstance()->getProject(projectId);

	if (IProject * project = qobject_cast<IProject*>(PluginManager::instance()->projects().value(description->getProjectType())))
	{
		QString pluginName = project->pluginFileName().split(".").at(0).section("lib", -1);
		QString pluginLangFile = pluginName + QString(".") + SettingsManager::instance()->value("language").toString() + ".qm";
		//QDir languagesDir = QDir(SettingsManager::instance()->value("languagesDir").toString());

		//QString languageName;
		//QDir appDir = QDir(QApplication::applicationDirPath());
		//if (appDir.isRelativePath(SettingsManager::instance()->value("languagesDir").toString()))
		//	languageName = appDir.absoluteFilePath(SettingsManager::instance()->value("languagesDir").toString() + QDir::separator() + pluginLangFile);
		//else
		//	languageName = QDir(SettingsManager::instance()->value("languagesDir").toString()).absoluteFilePath(pluginLangFile);

		//QTranslator translator;
		//translator.load(languageName);
		//QApplication::installTranslator(&translator);


		// start save thread

		//open project
		project->launch(description, SettingsManager::instance());

		//end saving thread

		//QApplication::removeTranslator(&translator);
		updateContents();
	}
}

void MyProjectsPage::onProjectListSelectionChanged()
{
	ui->deleteProjects->setEnabled(ui->projects->selectedItems().count() > 0);
	ui->deleteProjects->setDisabled(ui->projects->selectedItems().count() == 0);
	ui->deleteProjects->updatesEnabled();

	ui->linkProjects->setEnabled(false);
	ui->linkProjects->setDisabled(true);

	if (ui->projects->selectedItems().count() > 0)
	{
		QString projectID = ui->projects->currentItem()->data(2, Qt::UserRole).toString();
		IProjectDescription* projectInfo = Workspace::getInstance()->getProject(projectID);

		bool isLinkable = qobject_cast<IProjectContainer*>(PluginManager::instance()->projects().value(projectInfo->getProjectType())) != 0;

		ui->linkProjects->setEnabled(isLinkable);
		ui->linkProjects->setDisabled(!isLinkable);
	}

	ui->linkProjects->updatesEnabled();
}

void MyProjectsPage::onLinkProjectsClick()
{
	QString projectId = ui->projects->currentItem()->data(2, Qt::UserRole).toString();
	IProjectDescription * description = Workspace::getInstance()->getProject(projectId);

	LinkProjectsDialog dlgLinkProjects;
	dlgLinkProjects.setProject(description);
	dlgLinkProjects.exec();

	if (dlgLinkProjects.result() == QDialog::Accepted)
	{
		QSet<QString> referencedProjects = description->referencedProjects().toSet();
		QSet<QString> projectsToBeReferenced = dlgLinkProjects.linkedProjects().toSet();

		QSet<QString> projectsToBeUnlinked = (referencedProjects - projectsToBeReferenced);
		QSet<QString> projectsToBeLinked = (projectsToBeReferenced - referencedProjects);

		foreach(QString projectID, projectsToBeUnlinked)
		{
			IProjectDescription* project = Workspace::getInstance()->getProject(projectID);
			Workspace::getInstance()->unlinkProjects(project, description);
		}

		foreach(QString projectID, projectsToBeLinked)
		{
			IProjectDescription* project = Workspace::getInstance()->getProject(projectID);
			Workspace::getInstance()->linkProjects(project, description);
		}

		updateContents();
	}
}

void MyProjectsPage::onExportProjectsClick()
{
	ExportProjectsDialog dlgExport;
	dlgExport.exec();

	if (dlgExport.result() == QDialog::Accepted)
	{
		parentForm->setWidgetsEnabled(false);
		ActionProgressWidget* progressWidget = new ActionProgressWidget(parentForm);
		progressWidget->resize(400, 75);
		progressWidget->move(QPoint(parentForm->contentsRect().width()/2 - progressWidget->width()/2, parentForm->contentsRect().height()/2 - progressWidget->height()/2));
		progressWidget->show();
		QApplication::processEvents();

		QString selectedFolder = dlgExport.exportFolder();
		QStringList selectedProjects = dlgExport.selectedProjects();

		// exporting selected projects
		foreach(QString projectID, selectedProjects)
		{
			IProjectDescription* projectDescription = Workspace::getInstance()->getProject(projectID);

			progressWidget->setLabel(trUtf8("Exporting") + ": " + projectDescription->getProjectName());
			QApplication::processEvents();

			Workspace::getInstance()->exportProject(projectID, selectedFolder, progressWidget->progressBar());
		}

		// updating references on exported projects
		QHash<QString, IProjectDescription*> exportedProjects = Workspace::getInstance()->scanFolder(selectedFolder);
		foreach(IProjectDescription* exportedProject, exportedProjects)
		{
			if (!exportedProject->referencingProjects().isEmpty())
			{
				foreach(QString referencingProject, exportedProject->referencingProjects())
				{
					if (!exportedProjects.keys().contains(referencingProject))
					{
						ProjectDescription* exportedProjectDescription = new ProjectDescription(exportedProject->getProjectLocation());
						exportedProjectDescription->removeReferencingProject(referencingProject);
					}
				}
			}

			if (!exportedProject->referencedProjects().isEmpty())
			{
				foreach(QString referencedProject, exportedProject->referencedProjects())
				{
					if (!exportedProjects.keys().contains(referencedProject))
					{
						ProjectDescription* exportedProjectDescription = new ProjectDescription(exportedProject->getProjectLocation());
						exportedProjectDescription->removeReferencedProject(referencedProject);
					}
				}
			}
		}

		progressWidget->hide();
		delete progressWidget;
		parentForm->setWidgetsEnabled(true);
	}
}

void MyProjectsPage::onSyncProjectsClick()
{
	SyncProjectsDialog dlgSync;
	dlgSync.setWindowTitle(trUtf8("Update project(s)..."));
	dlgSync.exec();

	if (dlgSync.result() == QDialog::Accepted)
	{
		parentForm->setWidgetsEnabled(false);

		ActionProgressWidget* progressWidget = new ActionProgressWidget(parentForm);
		progressWidget->resize(400, 75);
		progressWidget->move(QPoint(parentForm->contentsRect().width()/2 - progressWidget->width()/2, parentForm->contentsRect().height()/2 - progressWidget->height()/2));
		progressWidget->show();
		QApplication::processEvents();

		if (dlgSync.selectedProjects().count() > 0)
		{		
			// update projects
			QString selectedFolder = dlgSync.sourceFolder();
			foreach(QString projectId, dlgSync.selectedProjects())
			{
				QDir sourceDir(selectedFolder);
				ProjectDescription * description = new ProjectDescription(sourceDir.absoluteFilePath(projectId));

				progressWidget->setLabel(trUtf8("Synchronizing") + ": " + description->getProjectName());
				QApplication::processEvents();

				if(Workspace::getInstance()->getProject(projectId))
					Workspace::getInstance()->syncProject(projectId, sourceDir.absoluteFilePath(projectId), progressWidget->progressBar());
				else
				{
					QDir workspaceDir(SettingsManager::instance()->value("workspaceDir").toString());
					FileSystemUtils::copyDirectory(sourceDir.absoluteFilePath(projectId), workspaceDir.absoluteFilePath(projectId), progressWidget->progressBar());
				}
			}

			// updating references on imported projects
			QHash<QString, IProjectDescription*> projectsInWorkspace = Workspace::getInstance()->scanFolder(Workspace::getInstance()->getPath());
			foreach(IProjectDescription* project, projectsInWorkspace)
			{
				if (!project->referencingProjects().isEmpty())
				{
					foreach(QString referencingProject, project->referencingProjects())
					{
						if (!projectsInWorkspace.keys().contains(referencingProject))
						{
							ProjectDescription* projectDescription = new ProjectDescription(project->getProjectLocation());
							projectDescription->removeReferencingProject(referencingProject);
						}
					}
				}

				if (!project->referencedProjects().isEmpty())
				{
					foreach(QString referencedProject, project->referencedProjects())
					{
						if (!projectsInWorkspace.keys().contains(referencedProject))
						{
							ProjectDescription* projectDescription = new ProjectDescription(project->getProjectLocation());
							projectDescription->removeReferencedProject(referencedProject);
						}
					}
				}
			}

			// reloading workspace
			Workspace::getInstance()->reload();
		}

		progressWidget->hide();
		delete progressWidget;
		parentForm->setWidgetsEnabled(true);
	}

	updateContents();
}

void MyProjectsPage::onDeleteProjectsClick()
{
	QString messageText = (ui->projects->selectedItems().count() == 1) ? trUtf8("Are you sure you want to remove the selected project?") : trUtf8("Are you sure you want to delete the selected projects?");
	QMessageBox warningMsg;
	warningMsg.setWindowTitle(trUtf8("Confirm"));
	warningMsg.setText(messageText);
    warningMsg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
	warningMsg.button(QMessageBox::Yes)->setText(trUtf8("Yes"));
	warningMsg.button(QMessageBox::No)->setText(trUtf8("No"));
//    warningMsg.button(QMessageBox::Yes)->setIcon(QIcon(QPixmap(":/icons/dialog-button-ok.png")));
//    warningMsg.button(QMessageBox::No)->setIcon(QIcon(QPixmap(":/icons/dialog-button-cancel.png")));

	warningMsg.exec();
	if (warningMsg.result() == QMessageBox::Yes)
	{
		parentForm->setWidgetsEnabled(false);

		ActionProgressWidget* progressWidget = new ActionProgressWidget(parentForm);
		progressWidget->resize(400, 75);
		progressWidget->move(QPoint(parentForm->contentsRect().width()/2 - progressWidget->width()/2, parentForm->contentsRect().height()/2 - progressWidget->height()/2));
		progressWidget->show();
		QApplication::processEvents();

		foreach(QTreeWidgetItem* item, ui->projects->selectedItems())
		{
//			QTreeWidgetItem * parentItem = item->parent();

			// removing project
			QString projectID = item->data(2, Qt::UserRole).toString();
			IProjectDescription* description = Workspace::getInstance()->getProject(projectID);

			progressWidget->setLabel(trUtf8("Removing") + ": " + description->getProjectName());
			QApplication::processEvents();

			Workspace::getInstance()->removeProject(projectID, progressWidget->progressBar());

			// removing item from tree
			QList<QTreeWidgetItem*> childItems = item->takeChildren();
			int itemIndex = ui->projects->indexOfTopLevelItem(item);
			ui->projects->takeTopLevelItem(itemIndex);
			delete item;

			if (!childItems.empty())
				ui->projects->addTopLevelItems(childItems);
		}

		progressWidget->hide();
		delete progressWidget;
		parentForm->setWidgetsEnabled(true);
		ui->projects->expandAll();
	}
}


