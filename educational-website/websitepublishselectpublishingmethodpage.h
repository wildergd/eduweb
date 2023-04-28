#ifndef WEBSITEPUBLISHSELECTPUBLISHINGMETHODPAGE_H
#define WEBSITEPUBLISHSELECTPUBLISHINGMETHODPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishSelectPublishingMethodPage;
}

class WebsitePublishSelectPublishingMethodPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishSelectPublishingMethodPage(QWidget *parent = 0);
    ~WebsitePublishSelectPublishingMethodPage();

    void setVisible(bool visible);
    int nextId() const;

private:
    Ui::WebsitePublishSelectPublishingMethodPage *ui;
};

#endif // WEBSITEPUBLISHSELECTPUBLISHINGMETHODPAGE_H
