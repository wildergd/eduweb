#include <QAbstractButton>
#include "websitepublishcddvddeployoptionspage.h"
#include "ui_websitepublishcddvddeployoptionspage.h"
#include "websitedeploywizard.h"

WebsitePublishCDDVDDeployOptionsPage::WebsitePublishCDDVDDeployOptionsPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishCDDVDDeployOptionsPage)
{
    ui->setupUi(this);

    /* configure fields */

    /* configure widgets */

    /* configure signals */
}

WebsitePublishCDDVDDeployOptionsPage::~WebsitePublishCDDVDDeployOptionsPage()
{
    delete ui;
}

void WebsitePublishCDDVDDeployOptionsPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
}

int WebsitePublishCDDVDDeployOptionsPage::nextId() const
{
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_DEPLOY_PROGRESS_PAGE;
}
