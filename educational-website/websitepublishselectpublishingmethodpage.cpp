#include <QAbstractButton>
#include "websitepublishselectpublishingmethodpage.h"
#include "ui_websitepublishselectpublishingmethodpage.h"
#include "websitedeploywizard.h"

WebsitePublishSelectPublishingMethodPage::WebsitePublishSelectPublishingMethodPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishSelectPublishingMethodPage)
{
    ui->setupUi(this);

    /* configure fields */
    registerField("publish2FTP", ui->publishFTP);
    registerField("publish2CD", ui->publishDVD);
    registerField("publish2FileSystem", ui->publishFolder);

    /* configure widgets */
    //wizard()->setOption(QWizard::HaveCustomButton1);

    ui->lbPublishFtpDescription->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    ui->lbPublishCDDVDDescription->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
    ui->lbPublishFilesystemDescription->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

    /* configure signals */
}

WebsitePublishSelectPublishingMethodPage::~WebsitePublishSelectPublishingMethodPage()
{
    delete ui;
}

void WebsitePublishSelectPublishingMethodPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, visible);
}

int WebsitePublishSelectPublishingMethodPage::nextId() const
{
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_FILESYSTEM_DEPLOY_OPTIONS_PAGE;
}
