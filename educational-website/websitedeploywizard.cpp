#include <QApplication>
#include <QDir>
#include "websitedeploywizard.h"
#include "ui_websitedeploywizard.h"
#include "websitepublishintropage.h"
#include "websitepublishselectdesignpage.h"
#include "websitepublishdesigncustomizationpage.h"
#include "websitepublishselectpublishingmethodpage.h"
#include "websitepublishftpdeployoptionspage.h"
#include "websitepublishcddvddeployoptionspage.h"
#include "websitepublishfilesystemdeployoptionspage.h"
#include "websitepublishdeployprogresspage.h"
#include "websitepublishdeployfinishedpage.h"
#include "templatefactory.h"

WebsiteDeployWizard::WebsiteDeployWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::WebsiteDeployWizard)
{
    /* init data */
    QDir appDir(qApp->applicationDirPath());
    TemplateFactory::getInstance()->load(appDir.absoluteFilePath("plugins/educational-website/templates"));

    /* configure widgets */
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog|Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    setButtonText(QWizard::CustomButton1, trUtf8("Preview"));

    setPixmap(QWizard::LogoPixmap, QPixmap(":/educational-website-icon.png"));

    setPage(WEBSITEPUBLISHWIZARD_INTRO_PAGE, new WebsitePublishIntroPage);
    setPage(WEBSITEPUBLISHWIZARD_SELECT_DESIGN_PAGE, new WebsitePublishSelectDesignPage);
    setPage(WEBSITEPUBLISHWIZARD_CUSTOMIZE_WEBSITE_PAGE, new WebsitePublishDesignCustomizationPage);
    setPage(WEBSITEPUBLISHWIZARD_SELECT_DEPLOY_METHOD_PAGE, new WebsitePublishSelectPublishingMethodPage);
    setPage(WEBSITEPUBLISHWIZARD_FTP_DEPLOY_OPTIONS_PAGE, new WebsitePublishFTPDeployOptionsPage);
    setPage(WEBSITEPUBLISHWIZARD_CDDVD_DEPLOY_OPTIONS_PAGE, new WebsitePublishCDDVDDeployOptionsPage);
    setPage(WEBSITEPUBLISHWIZARD_FILESYSTEM_DEPLOY_OPTIONS_PAGE, new WebsitePublishFilesystemDeployOptionsPage);
    setPage(WEBSITEPUBLISHWIZARD_DEPLOY_PROGRESS_PAGE, new WebsitePublishDeployProgressPage);
    setPage(WEBSITEPUBLISHWIZARD_DEPLOY_FINISHED_PAGE, new WebsitePublishDeployFinishedPage);

    setStartId(WEBSITEPUBLISHWIZARD_INTRO_PAGE);

    setButtonText(QWizard::CommitButton, trUtf8("Publish"));

    /* configure signals */
	connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(currentIdChanged(int)));
}

WebsiteDeployWizard::~WebsiteDeployWizard()
{
    delete ui;
}

QHash<QString, IProjectDescription*> & WebsiteDeployWizard::projects()
{
    return projectsList;
}

void WebsiteDeployWizard::setProjects(QList<IProjectDescription*> & projects)
{
    projectsList.empty();
    foreach(IProjectDescription* description, projects)
    {
        projectsList.insert(description->getProjectId(), description);
    }
}

void WebsiteDeployWizard::currentIdChanged(int id)
{
    if (id == WEBSITEPUBLISHWIZARD_DEPLOY_PROGRESS_PAGE)
    {
        ((WebsitePublishDeployProgressPage*) currentPage())->startPublishing();
    }
}
