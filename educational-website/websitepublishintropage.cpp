#include <QAbstractButton>
#include "websitepublishintropage.h"
#include "ui_websitepublishintropage.h"
#include "websitedeploywizard.h"

WebsitePublishIntroPage::WebsitePublishIntroPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishIntroPage)
{
    ui->setupUi(this);

    /* configure widgets */

    /* configure signals */
}

WebsitePublishIntroPage::~WebsitePublishIntroPage()
{
    delete ui;
}

void WebsitePublishIntroPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
}

int WebsitePublishIntroPage::nextId() const
{
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_SELECT_DESIGN_PAGE;
}
