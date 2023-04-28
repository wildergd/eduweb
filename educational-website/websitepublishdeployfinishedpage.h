#ifndef WEBSITEPUBLISHDEPLOYFINISHEDPAGE_H
#define WEBSITEPUBLISHDEPLOYFINISHEDPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishDeployFinishedPage;
}

class WebsitePublishDeployFinishedPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishDeployFinishedPage(QWidget *parent = 0);
    ~WebsitePublishDeployFinishedPage();

    void setVisible(bool visible);
    int nextId() const;

private:
    Ui::WebsitePublishDeployFinishedPage *ui;
};

#endif // WEBSITEPUBLISHDEPLOYFINISHEDPAGE_H
