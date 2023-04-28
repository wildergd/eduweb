#ifndef WEBSITEPUBLISHFTPDEPLOYOPTIONSPAGE_H
#define WEBSITEPUBLISHFTPDEPLOYOPTIONSPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishFTPDeployOptionsPage;
}

class WebsitePublishFTPDeployOptionsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishFTPDeployOptionsPage(QWidget *parent = 0);
    ~WebsitePublishFTPDeployOptionsPage();

    void setVisible(bool visible);
    int nextId() const;

private:
    Ui::WebsitePublishFTPDeployOptionsPage *ui;
};

#endif // WEBSITEPUBLISHFTPDEPLOYOPTIONSPAGE_H
