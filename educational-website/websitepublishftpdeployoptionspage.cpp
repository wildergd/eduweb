#include <QAbstractButton>
#include "websitepublishftpdeployoptionspage.h"
#include "ui_websitepublishftpdeployoptionspage.h"
#include "websitedeploywizard.h"

WebsitePublishFTPDeployOptionsPage::WebsitePublishFTPDeployOptionsPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishFTPDeployOptionsPage)
{
    ui->setupUi(this);

    /* configure fields */

    /* configure widgets */

    /* configure signals */
}

WebsitePublishFTPDeployOptionsPage::~WebsitePublishFTPDeployOptionsPage()
{
    delete ui;
}

void WebsitePublishFTPDeployOptionsPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
}

int WebsitePublishFTPDeployOptionsPage::nextId() const
{
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_DEPLOY_PROGRESS_PAGE;
}
