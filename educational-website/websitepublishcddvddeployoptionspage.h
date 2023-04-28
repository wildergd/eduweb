#ifndef WEBSITEPUBLISHCDDVDDEPLOYOPTIONSPAGE_H
#define WEBSITEPUBLISHCDDVDDEPLOYOPTIONSPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishCDDVDDeployOptionsPage;
}

class WebsitePublishCDDVDDeployOptionsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishCDDVDDeployOptionsPage(QWidget *parent = 0);
    ~WebsitePublishCDDVDDeployOptionsPage();

    void setVisible(bool visible);
    int nextId() const;

private:
    Ui::WebsitePublishCDDVDDeployOptionsPage *ui;
};

#endif // WEBSITEPUBLISHCDDVDDEPLOYOPTIONSPAGE_H
