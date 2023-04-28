#include <QStyleFactory>
#include "applicationsettingspage.h"
#include "ui_applicationsettingspage.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"

ApplicationSettingsPage::ApplicationSettingsPage(QWidget *parent) :
    MainFormPage(parent),
    ui(new Ui::ApplicationSettingsPage)
{
    /* configure widgets */
    ui->setupUi(this);

    foreach (QString key, QStyleFactory::keys())
		ui->selectedStyle->addItem(key, QVariant::fromValue(key));

	int currentStyleIndex = ui->selectedStyle->findText(SettingsManager::instance()->value("style").toString());
	ui->selectedStyle->setCurrentIndex((currentStyleIndex != -1) ? currentStyleIndex : 0);

    ui->lbLanguage->setHidden(true);
    ui->selectedLanguage->setHidden(true);
    ui->spacer2->changeSize(ui->spacer2->geometry().width(), 0);

    retranslateUI();

	/* configure signals */
	connect(ui->selectedStyle, SIGNAL(currentIndexChanged(QString)), this, SLOT(styleChanged(QString)));
	connect(ui->selectedLanguage, SIGNAL(currentIndexChanged(int)), this, SLOT(languageChanged(int)));
    connect(ui->workspaceFolder, SIGNAL(folderChanged()), this, SLOT(workspaceFolderChanged()));
}

ApplicationSettingsPage::~ApplicationSettingsPage()
{
    delete ui;
}

void ApplicationSettingsPage::retranslateUI()
{
    ui->lbStyle->setText(trUtf8("Window theme"));
    ui->lbLanguage->setText(trUtf8("Language"));
    ui->lbWorkspaceDir->setText(trUtf8("Folder to store all your projects"));
}

void ApplicationSettingsPage::updateContents()
{
	ui->selectedStyle->setCurrentIndex(ui->selectedStyle->findData(SettingsManager::instance()->value("style").toString()));
	ui->selectedLanguage->setCurrentIndex(ui->selectedLanguage->findData(SettingsManager::instance()->value("language").toString()));
    ui->workspaceFolder->setFolder(SettingsManager::instance()->value("workspaceDir").toString());
}

void ApplicationSettingsPage::showEvent(QShowEvent * event)
{
        Q_UNUSED(event);
}

void ApplicationSettingsPage::styleChanged(const QString & text)
{
	QApplication::setStyle(QStyleFactory::create(text));
	SettingsManager::instance()->setValue("style", QVariant::fromValue(text));
	emit configParamValueChanged("style");
}

void ApplicationSettingsPage::languageChanged(int index)
{
}

void ApplicationSettingsPage::workspaceFolderChanged()
{
    SettingsManager::instance()->setValue("workspaceDir", QVariant::fromValue(ui->workspaceFolder->folder()));
    Workspace::getInstance()->load(ui->workspaceFolder->folder());
    emit configParamValueChanged("workspaceDir");
}
