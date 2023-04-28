#ifndef WEBSITEPUBLISHFILESYSTEMDEPLOYOPTIONSPAGE_H
#define WEBSITEPUBLISHFILESYSTEMDEPLOYOPTIONSPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishFilesystemDeployOptionsPage;
}

class WebsitePublishFilesystemDeployOptionsPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishFilesystemDeployOptionsPage(QWidget *parent = 0);
    ~WebsitePublishFilesystemDeployOptionsPage();

    void setVisible(bool visible);
    bool isComplete() const;
    int nextId() const;

private:
    Ui::WebsitePublishFilesystemDeployOptionsPage *ui;
};

#endif // WEBSITEPUBLISHFILESYSTEMDEPLOYOPTIONSPAGE_H
