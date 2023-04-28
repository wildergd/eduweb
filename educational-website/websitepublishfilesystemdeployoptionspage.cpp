#include <QAbstractButton>
#include "websitepublishfilesystemdeployoptionspage.h"
#include "ui_websitepublishfilesystemdeployoptionspage.h"
#include "websitedeploywizard.h"
#include "folderselectwidget.h"

WebsitePublishFilesystemDeployOptionsPage::WebsitePublishFilesystemDeployOptionsPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishFilesystemDeployOptionsPage)
{
    /* configure widgets */
    ui->setupUi(this);

    /* configure fields */
    setCommitPage(true);
    registerField("outFolder", ui->folderSelectWidget, "folder", SIGNAL(folderChanged()));

    /* configure signals */
    connect(ui->folderSelectWidget, SIGNAL(folderChanged()), this, SIGNAL(completeChanged()));
}

WebsitePublishFilesystemDeployOptionsPage::~WebsitePublishFilesystemDeployOptionsPage()
{
    delete ui;
}

void WebsitePublishFilesystemDeployOptionsPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
}

bool WebsitePublishFilesystemDeployOptionsPage::isComplete() const
{
    return !field("outFolder").toString().isEmpty();
}

int WebsitePublishFilesystemDeployOptionsPage::nextId() const
{
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_DEPLOY_PROGRESS_PAGE;
}
