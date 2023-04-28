#ifndef WEBSITEDEPLOYWIZARD_H
#define WEBSITEDEPLOYWIZARD_H

#include <QWizard>
#include <QHash>
#include "iprojectdescription.h"

namespace Ui {
    class WebsiteDeployWizard;
}

class WebsiteDeployWizard : public QWizard
{
    Q_OBJECT

public:
    enum
    {
        WEBSITEPUBLISHWIZARD_INTRO_PAGE,
        WEBSITEPUBLISHWIZARD_SELECT_DESIGN_PAGE,
        WEBSITEPUBLISHWIZARD_CUSTOMIZE_WEBSITE_PAGE,
        WEBSITEPUBLISHWIZARD_SELECT_DEPLOY_METHOD_PAGE,
        WEBSITEPUBLISHWIZARD_FTP_DEPLOY_OPTIONS_PAGE,
        WEBSITEPUBLISHWIZARD_CDDVD_DEPLOY_OPTIONS_PAGE,
        WEBSITEPUBLISHWIZARD_FILESYSTEM_DEPLOY_OPTIONS_PAGE,
        WEBSITEPUBLISHWIZARD_DEPLOY_PROGRESS_PAGE,
        WEBSITEPUBLISHWIZARD_DEPLOY_FINISHED_PAGE
    };

    explicit WebsiteDeployWizard(QWidget *parent = 0);
    ~WebsiteDeployWizard();

    QHash<QString, IProjectDescription*> & projects();
    void setProjects(QList<IProjectDescription*> & projects);

private:
    Ui::WebsiteDeployWizard *ui;

    QHash<QString, IProjectDescription*> projectsList;
    int topLevelProjectsLength;

private slots:
    void currentIdChanged(int id);
};

#endif // WEBSITEDEPLOYWIZARD_H
