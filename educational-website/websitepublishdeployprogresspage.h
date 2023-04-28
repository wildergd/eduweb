#ifndef WEBSITEPUBLISHDEPLOYPROGRESSPAGE_H
#define WEBSITEPUBLISHDEPLOYPROGRESSPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishDeployProgressPage;
}

class WebsitePublishDeployProgressPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishDeployProgressPage(QWidget *parent = 0);
    ~WebsitePublishDeployProgressPage();

    void setVisible(bool visible);
    bool isComplete() const;
    void initializePage();
    int nextId() const;
    void startPublishing();

private:
    Ui::WebsitePublishDeployProgressPage *ui;
    bool published;

    void publishToFTP();
    void publishToDVD();
    void publishToFileSystem();
};

#endif // WEBSITEPUBLISHDEPLOYPROGRESSPAGE_H
