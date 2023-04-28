#include <QAbstractButton>
#include "websitepublishselectdesignpage.h"
#include "ui_websitepublishselectdesignpage.h"
#include "websitedeploywizard.h"
#include "templatefactory.h"

WebsitePublishSelectDesignPage::WebsitePublishSelectDesignPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishSelectDesignPage)
{
    /* configure widgets */
    ui->setupUi(this);
    updateStyles();

    /* configure signals */
    connect(ui->templates, SIGNAL(itemSelectionChanged()), this, SIGNAL(completeChanged()));

    /* configure fields */
    registerField("template", ui->templates);
}

WebsitePublishSelectDesignPage::~WebsitePublishSelectDesignPage()
{
    delete ui;
}

void WebsitePublishSelectDesignPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
}

void WebsitePublishSelectDesignPage::updateStyles()
{
    QPalette palette = QApplication::palette();
    ui->templates->setStyleSheet(""
        "QListView {show-decoration-selected: 1;}"
        "QListView::item {width: 110px;border: 1px solid rgba(" + QString::number(palette.window().color().red(), 10) + ", " + QString::number(palette.window().color().green(), 10) + ", " + QString::number(palette.window().color().blue(), 10) + ", 255);}"
        "QListView::text {width: 100px;margin: 1px;padding:0px;subcontrol-origin: border;subcontrol-position: bottom center;}"
        "QListView::item:selected:active, QListView::item:selected:!active {border: 1px solid rgba(" + QString::number(palette.highlight().color().red(), 10) + ", " + QString::number(palette.highlight().color().green(), 10) + ", " + QString::number(palette.highlight().color().blue(), 10) + ", 255);background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgba(" + QString::number(palette.highlight().color().red(), 10) + ", " + QString::number(palette.highlight().color().green(), 10) + ", " + QString::number(palette.highlight().color().blue(), 10) + ", 200), stop: 1 rgba(" + QString::number(palette.highlight().color().red(), 10) + ", " + QString::number(palette.highlight().color().green(), 10) + ", " + QString::number(palette.highlight().color().blue(), 10) + ", 255)); color: " + palette.highlightedText().color().name() + ";}"
        "QListView::item:hover {border: 1px groove rgba(" + QString::number(palette.highlight().color().red(), 10) + ", " + QString::number(palette.highlight().color().green(), 10) + ", " + QString::number(palette.highlight().color().blue(), 10) + ", 255);background-color: rgba(" + QString::number(palette.highlight().color().red(), 10) + ", " + QString::number(palette.highlight().color().green(), 10) + ", " + QString::number(palette.highlight().color().blue(), 10) + ", 100);color: " + palette.highlightedText().color().name() + ";}"
    );
}

bool WebsitePublishSelectDesignPage::isComplete() const
{
    return ui->templates->currentRow() != -1;
}

void WebsitePublishSelectDesignPage::initializePage()
{
    ui->templates->clearFocus();
    ui->templates->clearSelection();
    updateTemplatesList();

    if (field("template").toInt() != -1)
        ui->templates->setCurrentRow(field("template").toInt());
}

int WebsitePublishSelectDesignPage::nextId() const
{
    if (ui->templates->currentRow() >= 0)
    {
        Template selectedTemplate = TemplateFactory::getInstance()->templates().at(ui->templates->currentRow());
        return (selectedTemplate.configParams().count() > 0 ) ? WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_CUSTOMIZE_WEBSITE_PAGE : WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_SELECT_DEPLOY_METHOD_PAGE;
    }
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_CUSTOMIZE_WEBSITE_PAGE;
}

void WebsitePublishSelectDesignPage::updateTemplatesList()
{
    ui->templates->clear();

    QList<Template> webTemplates = TemplateFactory::getInstance()->templates();
    if (webTemplates.isEmpty())
        return;

    foreach (Template webTemplate, webTemplates)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(webTemplate.name());
        item->setIcon(QIcon(webTemplate.screenshot()));
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setToolTip("<p align=\"center\" style=\"margin:5px; padding:5px;\"><br/><img src=\"" + webTemplate.screenshotPath() + "\" width=\"200\" height=\"150\" /><br />" + webTemplate.description() + "</p>");

        ui->templates->addItem(item);
    }

    ui->templates->clearFocus();
    ui->templates->clearSelection();
}
