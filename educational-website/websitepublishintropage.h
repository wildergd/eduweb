#ifndef WEBSITEPUBLISHINTROPAGE_H
#define WEBSITEPUBLISHINTROPAGE_H

#include <QWizardPage>

namespace Ui {
    class WebsitePublishIntroPage;
}

class WebsitePublishIntroPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit WebsitePublishIntroPage(QWidget *parent = 0);
    ~WebsitePublishIntroPage();

    void setVisible(bool visible);
    int nextId() const;

private:
    Ui::WebsitePublishIntroPage *ui;
};

#endif // WEBSITEPUBLISHINTROPAGE_H
