#ifndef WEBSITEPUBLISHSELECTDESIGNPAGE_H
#define WEBSITEPUBLISHSELECTDESIGNPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishSelectDesignPage;
}

class WebsitePublishSelectDesignPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishSelectDesignPage(QWidget *parent = 0);
    ~WebsitePublishSelectDesignPage();

    void setVisible(bool visible);
    void updateStyles();

    bool isComplete() const;
    void initializePage();
    int nextId() const;

private:
    Ui::WebsitePublishSelectDesignPage *ui;

    void updateTemplatesList();
};

#endif // WEBSITEPUBLISHSELECTDESIGNPAGE_H
