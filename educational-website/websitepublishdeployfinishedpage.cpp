#include <QAbstractButton>
#include "websitepublishdeployfinishedpage.h"
#include "ui_websitepublishdeployfinishedpage.h"
#include "websitedeploywizard.h"

WebsitePublishDeployFinishedPage::WebsitePublishDeployFinishedPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishDeployFinishedPage)
{
    ui->setupUi(this);

    /* configure fields */

    /* configure widgets */

    /* configure signals */
}

WebsitePublishDeployFinishedPage::~WebsitePublishDeployFinishedPage()
{
    delete ui;
}

void WebsitePublishDeployFinishedPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, !visible);
    wizard()->setOption(QWizard::NoCancelButton, visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
}

int WebsitePublishDeployFinishedPage::nextId() const
{
    return -1;
}
