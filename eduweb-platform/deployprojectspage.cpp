#include <QPushButton>
#include "deployprojectspage.h"
#include "ui_deployprojectspage.h"
#include "deployprojectdialog.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "iconfigurable.h"
#include "workspace.h"

DeployProjectsPage::DeployProjectsPage(QWidget *parent) :
    MainFormPage(parent),
    ui(new Ui::DeployProjectsPage)
{
    /* configure widgets */
    ui->setupUi(this);
    retranslateUI();

    ui->horizontalLayout->removeItem(ui->horizontalSpacer);
    ui->horizontalLayout->removeWidget(ui->configButton);
    delete ui->configButton;
    delete ui->horizontalSpacer;

    /* configure signals */
    //connect(ui->availableDeployers, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(onDeployProjectSelect(QListWidgetItem*)));
    connect(ui->availableDeployers, SIGNAL(onDblClickItem(QTreeWidgetItem*,int)), this, SLOT(onDeployProjectSelect(QTreeWidgetItem*,int)));
}

DeployProjectsPage::~DeployProjectsPage()
{
    delete ui;
}

void DeployProjectsPage::retranslateUI()
{
	ui->hint->setText(trUtf8("Double-click to select the deploy option"));
}

void DeployProjectsPage::updateContents()
{
	setEnabled(PluginManager::instance()->deployers().count() > 0);
	setDisabled(PluginManager::instance()->deployers().count() == 0);
	updatesEnabled();

	ui->availableDeployers->clear();

    QHash<QString, QObject*> deployers = PluginManager::instance()->deployers();
	if (deployers.count() == 0)
		return;

    foreach (QObject* plugin, deployers)
	{
        IDeployer* deployer = qobject_cast<IDeployer*>(plugin);
        QTreeWidgetItem *item = ui->availableDeployers->addItem(deployer->group());

        //QListWidgetItem *item = new QListWidgetItem(ui->availableDeployers);

        //QString deployerName = deployer->pluginFileName().split(".").at(0).section("lib", -1);
        //QString deployerLangFile = deployerName + QString(".") + SettingsManager::instance()->value("language").toString() + ".qm";
		//QDir languagesDir = QDir(SettingsManager::instance()->value("languagesDir").toString());

		//QString languageName;
		//QDir appDir = QDir(QApplication::applicationDirPath());
		//if (appDir.isRelativePath(SettingsManager::instance()->value("languagesDir").toString()))
		//	languageName = appDir.absoluteFilePath(SettingsManager::instance()->value("languagesDir").toString() + QDir::separator() + deployerLangFile);
		//else
		//	languageName = QDir(SettingsManager::instance()->value("languagesDir").toString()).absoluteFilePath(deployerLangFile);

		//QTranslator translator;
		//translator.load(languageName);
		//QApplication::installTranslator(&translator);
		
        item->setText(0, deployer->pluginDisplayName());
        item->setToolTip(0, deployer->pluginDescription());
        item->setIcon(0, QIcon(QPixmap(deployer->pluginIcon()).scaled(48, 48, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setData(0, Qt::UserRole, QVariant::fromValue(deployer->pluginName()));

        if (qobject_cast<IConfigurable*>(plugin))
        {
            ItemConfigButton* pushButton = new ItemConfigButton();
            pushButton->setText(trUtf8("Configure"));
            pushButton->setData(QVariant::fromValue(deployer->pluginName()));
            pushButton->setFixedWidth(80);
            pushButton->setFixedHeight(25);

            item->treeWidget()->setItemWidget(item, 1, pushButton);

            connect(pushButton, SIGNAL(onButtonClicked(ItemConfigButton*)), this, SLOT(onConfigButtonClick(ItemConfigButton*)));

            item->treeWidget()->setItemWidget(item, 1, pushButton);
        }

		//QApplication::removeTranslator(&translator);
	}
}

void DeployProjectsPage::showEvent(QShowEvent * event)
{
        Q_UNUSED(event);
        ui->availableDeployers->clearSelection();
}

//void DeployProjectsPage::onDeployProjectSelect(QListWidgetItem *current)
void DeployProjectsPage::onDeployProjectSelect(QTreeWidgetItem* item, int column)
{
//	Q_UNUSED(current);
//    QString deployerIndex = ui->availableDeployers->item(ui->availableDeployers->currentRow())->data(Qt::UserRole).toString();
    QString deployerIndex = item->data(0, Qt::UserRole).toString();
    IDeployer * deployer = qobject_cast<IDeployer*>(PluginManager::instance()->deployers().value(deployerIndex));
	if (!deployer)
		return;

	DeployProjectDialog dlgDeployDlg;
	dlgDeployDlg.setProjectTypes(deployer->getCompatibleProjects());
	dlgDeployDlg.exec();

	if (dlgDeployDlg.result() != QDialog::Accepted)
		return;

	// activate deployer
	if (dlgDeployDlg.selectedProjects().count() == 0)
		return;

	QList<IProjectDescription*> selectedProjects;
	foreach(QString projectId, dlgDeployDlg.selectedProjects())
		addProjectBranchToList(projectId, selectedProjects);

    //QString deployerName = deployer->pluginFileName().split(".").at(0).section("lib", -1);
	//QString deployerLangFile = deployerName + QString(".") + SettingsManager::instance()->value("language").toString() + ".qm";
	//QDir languagesDir = QDir(SettingsManager::instance()->value("languagesDir").toString());

	//QString languageName;
	//QDir appDir = QDir(QApplication::applicationDirPath());
	//if (appDir.isRelativePath(SettingsManager::instance()->value("languagesDir").toString()))
	//	languageName = appDir.absoluteFilePath(SettingsManager::instance()->value("languagesDir").toString() + QDir::separator() + deployerLangFile);
	//else
	//	languageName = QDir(SettingsManager::instance()->value("languagesDir").toString()).absoluteFilePath(deployerLangFile);

	//QTranslator translator;
	//translator.load(languageName);
	//QApplication::installTranslator(&translator);

    deployer->launch(selectedProjects, dlgDeployDlg.selectedProjectType(), SettingsManager::instance());

    //QApplication::removeTranslator(&translator);*/
}

void DeployProjectsPage::addProjectBranchToList(QString projectId, QList<IProjectDescription*> & projectsList)
{
	IProjectDescription * description = Workspace::getInstance()->getProject(projectId);
	if (!PluginManager::instance()->projects().value(description->getProjectType()))
		return;

	projectsList.append(description);

	if (description->referencedProjects().count() == 0)
		return;

	foreach(QString referencedProjectId, description->referencedProjects())
		addProjectBranchToList(referencedProjectId, projectsList);
}

void DeployProjectsPage::onConfigButtonClick(ItemConfigButton* button)
{
    QString projectIndex = button->data().toString();
    IConfigurable* deployer = qobject_cast<IConfigurable*>(PluginManager::instance()->deployers().value(projectIndex));
    deployer->launchConfig(SettingsManager::instance());
//    SettingsManager::instance()->sync();
}
