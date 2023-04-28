#include <QGroupBox>
//#include <QVBoxLayout>
//#include <QHBoxLayout>
#include <QLineEdit>
#include <QAbstractButton>
#include "websitepublishdesigncustomizationpage.h"
#include "ui_websitepublishdesigncustomizationpage.h"
#include "websitedeploywizard.h"
#include "templatefactory.h"
#include "richeditorwidget.h"
#include "fileselectwidget.h"

WebsitePublishDesignCustomizationPage::WebsitePublishDesignCustomizationPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishDesignCustomizationPage)
{
    ui->setupUi(this);

    /* configure fields */
    registerField("templateConfigParams", this);

    /* configure widgets */

    /* configure signals */
}

WebsitePublishDesignCustomizationPage::~WebsitePublishDesignCustomizationPage()
{
    delete ui;
}

void WebsitePublishDesignCustomizationPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
}

void WebsitePublishDesignCustomizationPage::updateStyles()
{

}

int WebsitePublishDesignCustomizationPage::nextId() const
{
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_SELECT_DEPLOY_METHOD_PAGE;
}

void WebsitePublishDesignCustomizationPage::initializePage()
{
    int templateIndex = field("template").toInt();
    Template selectedTemplate = TemplateFactory::getInstance()->templates().at(templateIndex);

    if (selectedTemplate.configParams().count() == 0)
        return ;

    QWidget* container = new QWidget;
    ui->scrollArea->setWidget(container);
    container->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    QVBoxLayout * containerLayout = new QVBoxLayout;
    container->setLayout(containerLayout);
    containerLayout->setMargin(0);

    foreach(TemplateConfigParam param, selectedTemplate.configParams())
    {
        containerLayout->addWidget(createTemplateParamWidget(param));
    }
}

QWidget* WebsitePublishDesignCustomizationPage::createTemplateParamWidget(TemplateConfigParam & param)
{
    QWidget * control;
    QString paramType("");

    if (param.type().compare("string", Qt::CaseInsensitive) == 0)
    {
        control = new QLineEdit;
        paramType = "TypeString";
    }
    else if (param.type().compare("text", Qt::CaseInsensitive) == 0)
    {
        control = new RichEditorWidget;
        ((RichEditorWidget*) control)->textEditor()->setTabChangesFocus(true);
        paramType = "TypeText";
    }
    else if (param.type().compare("file", Qt::CaseInsensitive) == 0)
    {
        control = new FileSelectWidget;
        paramType = "TypeFile";
    }
    else if (param.type().compare("image", Qt::CaseInsensitive) == 0)
    {
        control = new FileSelectWidget;
        ((FileSelectWidget *) control)->setFilter("*.png *.jpg *.gif");
        paramType = "TypeImage";
    }
    else
    {
        return 0;
    }

    QStringList configParams = field("templateConfigParams").toStringList();
    QString fieldName = "configParam_" + paramType + "_" + param.varName();

    if (!configParams.contains(fieldName))
        configParams.append(fieldName);

    setField("templateConfigParams", QVariant::fromValue(configParams));

    QGroupBox * widget = new QGroupBox;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(4);

    widget->setTitle(param.name());
    widget->setFlat(true);
    control->setObjectName(fieldName);
    control->setToolTip(param.description());

    layout->addWidget(control);

    widget->setFocusProxy(control);
    widget->setLayout(layout);

    QString mandatoryChar = (param.mandatory()) ? "*" : "";
    registerField(fieldName + mandatoryChar, control);

    return widget;
}
