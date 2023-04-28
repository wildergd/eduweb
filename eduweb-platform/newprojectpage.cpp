#include <QMessageBox>
#include <QPushButton>
#include "newprojectpage.h"
#include "ui_newprojectpage.h"
#include "newprojectdialog.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"
#include "iconfigurable.h"
#include "actionprogresswidget.h"
#include "itemconfigbutton.h"

NewProjectPage::NewProjectPage(QWidget *parent) :
    MainFormPage(parent),
    ui(new Ui::NewProjectPage)
{
    /* configure widgets */
    ui->setupUi(this);
    retranslateUI();

    ui->horizontalLayout->removeItem(ui->horizontalSpacer);
    ui->horizontalLayout->removeWidget(ui->configButton);
    delete ui->configButton;
    delete ui->horizontalSpacer;

    /* configure signals */
    //connect(ui->availableProjects, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onAvailableProjectsItemClicked(QListWidgetItem*)));
    //connect(ui->availableProjects, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(onNewProjectSelect(QListWidgetItem*)));
    //connect(ui->configButton, SIGNAL(clicked()), this, SLOT(onConfigButtonClick()));
    connect(ui->availableProjects, SIGNAL(onDblClickItem(QTreeWidgetItem*,int)), this, SLOT(onNewProjectSelect(QTreeWidgetItem*,int)));
}

NewProjectPage::~NewProjectPage()
{
    delete ui;
}

void NewProjectPage::retranslateUI()
{
    ui->retranslateUi(this);
    //ui->hint->setText(trUtf8("Double-click to select the kind of project you want to create"));
}

void NewProjectPage::updateContents()
{
    setEnabled(PluginManager::instance()->projects().count() > 0);
	setDisabled(PluginManager::instance()->projects().count() == 0);
	updatesEnabled();

	ui->availableProjects->clear();
	QHash<QString, QObject*> projectTypes = PluginManager::instance()->projects();

	if (projectTypes.count() == 0)
		return;

	foreach(QObject* plugin, projectTypes)
	{
        IProject* project = qobject_cast<IProject*>(plugin);
        QTreeWidgetItem *item = ui->availableProjects->addItem(project->group());
        //QListWidgetItem *item = new QListWidgetItem(ui->availableProjects);

        //QString projectName = project->pluginFileName().split(".").at(0).section("lib", -1);
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
		
        item->setText(0, project->pluginDisplayName());
        item->setToolTip(0, project->pluginDescription());
        item->setIcon(0, QIcon(QPixmap(project->pluginIcon()).scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setData(0, Qt::UserRole, QVariant::fromValue(project->pluginName()));

        if (qobject_cast<IConfigurable*>(plugin))
        {
            ItemConfigButton* pushButton = new ItemConfigButton();
            pushButton->setText(trUtf8("Configure"));
            pushButton->setData(QVariant::fromValue(project->pluginName()));
            pushButton->setFixedWidth(80);
            pushButton->setFixedHeight(25);

            item->treeWidget()->setItemWidget(item, 1, pushButton);

            connect(pushButton, SIGNAL(onButtonClicked(ItemConfigButton*)), this, SLOT(onConfigButtonClick(ItemConfigButton*)));
        }

		//QApplication::removeTranslator(&translator);
	}
}

void NewProjectPage::showEvent(QShowEvent * event)
{
    Q_UNUSED(event);
    ui->availableProjects->clearSelection();
    //ui->configButton->setEnabled(false);
}

//void NewProjectPage::onNewProjectSelect(QListWidgetItem *current)
void NewProjectPage::onNewProjectSelect(QTreeWidgetItem* item, int column)
{
    //Q_UNUSED(current);
    //QString projectIndex = ui->availableProjects->item(ui->availableProjects->currentRow())->data(Qt::UserRole).toString();
    QString projectIndex = item->data(0, Qt::UserRole).toString();

	NewProjectDialog dlgNewProject;
	dlgNewProject.setProjectType(projectIndex);
	dlgNewProject.exec();
	if (dlgNewProject.result() != QDialog::Accepted)
		return;
		
	IProjectDescription * description = NULL;
    if (!dlgNewProject.cloneExisting())
	{
		// new empty project
		description = Workspace::getInstance()->createProject(dlgNewProject.title());
	}
	else
	{
		parentForm->setWidgetsEnabled(false);

		ActionProgressWidget* progressWidget = new ActionProgressWidget(parentForm);
		progressWidget->resize(400, 75);
		progressWidget->move(QPoint(parentForm->contentsRect().width()/2 - progressWidget->width()/2, parentForm->contentsRect().height()/2 - progressWidget->height()/2));
		progressWidget->show();
		QApplication::processEvents();

		// clone existing project
		progressWidget->setLabel(trUtf8("Creating project") + ": " + dlgNewProject.title());
		QApplication::processEvents();

		description = Workspace::getInstance()->createProjectFromExisting(dlgNewProject.source(), dlgNewProject.title(), progressWidget->progressBar());

		progressWidget->hide();
		delete progressWidget;
		parentForm->setWidgetsEnabled(true);

		if (!description)
			return;
	}

	if (dlgNewProject.isLinked())
	{
		IProjectDescription* projectLinkedTo = Workspace::getInstance()->getProject(dlgNewProject.linkingProject());
		Workspace::getInstance()->linkProjects(description, projectLinkedTo);
	}

	IProject * project = qobject_cast<IProject*>(PluginManager::instance()->projects().value(projectIndex));
	if (!project)
		return;
		
	description->setProjectType(project->pluginName());

    //QString pluginName = project->pluginFileName().split(".").at(0).section("lib", -1);
    //QString pluginLangFile = pluginName + QString(".") + SettingsManager::instance()->value("language").toString() + ".qm";
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

    project->launch(description, SettingsManager::instance());

    //ProjectLaunchThread thread(project, description);
    //thread.start();
    //thread.wait();

    //QApplication::removeTranslator(&translator);
}

void NewProjectPage::onAvailableProjectsItemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
//    QString projectIndex = ui->availableProjects->item(ui->availableProjects->currentRow())->data(Qt::UserRole).toString();
//    IConfigurable * project = qobject_cast<IConfigurable*>(PluginManager::instance()->projects().value(projectIndex));
//    ui->configButton->setEnabled(project != NULL);
}

void NewProjectPage::onConfigButtonClick(ItemConfigButton* button)
{
    QString projectIndex = button->data().toString();
    IConfigurable* project = qobject_cast<IConfigurable*>(PluginManager::instance()->projects().value(projectIndex));
    project->launchConfig(SettingsManager::instance());
//    SettingsManager::instance()->sync();
}

