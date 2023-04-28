#ifndef WEBSITEPUBLISHDESIGNCUSTOMIZATIONPAGE_H
#define WEBSITEPUBLISHDESIGNCUSTOMIZATIONPAGE_H

#include <QWizardPage>
#include <QWidget>
#include "templateconfigparam.h"

namespace Ui {
    class WebsitePublishDesignCustomizationPage;
}

class WebsitePublishDesignCustomizationPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishDesignCustomizationPage(QWidget *parent = 0);
    ~WebsitePublishDesignCustomizationPage();

    void setVisible(bool visible);
    void updateStyles();

    void initializePage();
    int nextId() const;

private:
    Ui::WebsitePublishDesignCustomizationPage* ui;

    QWidget* createTemplateParamWidget(TemplateConfigParam & param);
};

#endif // WEBSITEPUBLISHDESIGNCUSTOMIZATIONPAGE_H
