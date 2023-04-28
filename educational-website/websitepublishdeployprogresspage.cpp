#include <QAbstractButton>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QStringList>
#include <QListWidgetItem>
#include <QPixmap>
#include <QIcon>
#include <QHash>
#include <QSettings>
#include "websitepublishdeployprogresspage.h"
#include "ui_websitepublishdeployprogresspage.h"
#include "websitedeploywizard.h"
#include "filesystemutils.h"
#include "zipfile.h"
#include "templatefactory.h"

WebsitePublishDeployProgressPage::WebsitePublishDeployProgressPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::WebsitePublishDeployProgressPage)
{
    /* configure widgets */
    ui->setupUi(this);
    ui->progressBar->setMaximum(0);
    ui->progressBar->reset();

    /* configure signals */
}

WebsitePublishDeployProgressPage::~WebsitePublishDeployProgressPage()
{
    delete ui;
}

void WebsitePublishDeployProgressPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);
    wizard()->setOption(QWizard::HaveHelpButton, visible);
    wizard()->setOption(QWizard::NoCancelButton, !visible);
    wizard()->setOption(QWizard::HaveCustomButton1, !visible);
    wizard()->button(QWizard::CancelButton)->setEnabled(!visible);
    wizard()->button(QWizard::CancelButton)->setDisabled(visible);
    wizard()->button(QWizard::CancelButton)->updatesEnabled();
}

int WebsitePublishDeployProgressPage::nextId() const
{
    return WebsiteDeployWizard::WEBSITEPUBLISHWIZARD_DEPLOY_FINISHED_PAGE;
}

bool WebsitePublishDeployProgressPage::isComplete() const
{
    return published;
}

void WebsitePublishDeployProgressPage::initializePage()
{
    published = false;
}

void WebsitePublishDeployProgressPage::startPublishing()
{
    if (field("publish2FTP").toBool())
    {
        publishToFTP();
    }
    else if (field("publish2CD").toBool())
    {
        publishToDVD();
    }
    else if (field("publish2FileSystem").toBool())
    {
        publishToFileSystem();
    }

    emit completeChanged();

    if (published)
        wizard()->next();
}

void WebsitePublishDeployProgressPage::publishToFTP()
{
    QStringList stages;
    stages << trUtf8("Creating structure...");
    stages << trUtf8("Publishing metadata...");
    stages << trUtf8("Uploading files...");
    stages << trUtf8("Applying template...");
    stages << trUtf8("Customizing template...");
}

void WebsitePublishDeployProgressPage::publishToDVD()
{
}

void WebsitePublishDeployProgressPage::publishToFileSystem()
{
    QStringList stages;
    stages << trUtf8("Creating structure...");
    stages << trUtf8("Publishing metadata...");
    stages << trUtf8("Copying files...");
    stages << trUtf8("Applying template...");
    stages << trUtf8("Customizing template...");

    ui->publishLog->clear();

    QPixmap emptyPixmap = QPixmap(QSize(16, 16));
    emptyPixmap.fill(Qt::transparent);

    foreach(QString stage, stages)
    {
        QListWidgetItem * item = new QListWidgetItem(ui->publishLog);
        item->setText(stage);
        item->setIcon(QIcon(emptyPixmap));
        item->setFont(ui->publishLog->font());
        item->setFlags(Qt::ItemIsEnabled);
    }

    ui->progressBar->setVisible(false);
    QApplication::processEvents();

    int templateIndex = field("template").toInt();
    Template selectedTemplate = TemplateFactory::getInstance()->templates().at(templateIndex);

    QString templatePath = TemplateFactory::getInstance()->absolutePath() + QDir::separator() + selectedTemplate.id();
    QString outputFolder = wizard()->field("outFolder").toString();

    if (!(outputFolder.isEmpty() || outputFolder.isNull()))
    {
        int lastIndex = 0;
        bool errorOcurr = false;
        QDir outputDir(outputFolder);
        QDir appDir(QApplication::applicationDirPath());

        QFont font = ui->publishLog->font();
        font.setBold(true);

        // stage #1
        ui->publishLog->item(lastIndex)->setIcon(QIcon(":/teacher-web/icons/current.png"));
        ui->publishLog->item(lastIndex)->setFont(font);
        ui->progressBar->setVisible(true);
        QApplication::processEvents();

        ZipFile::unzipFile(appDir.absoluteFilePath("plugins/educational-website/cdapp.zip"), outputFolder, ui->progressBar);

#if defined(Q_OS_LINUX)
        QFile::setPermissions(outputDir.absoluteFilePath("bin/runcd"), QFile::WriteOwner|QFile::ReadOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
        QFile::setPermissions(outputDir.absoluteFilePath("bin/runcd.exe"), QFile::WriteOwner|QFile::ReadOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
        QFile::setPermissions(outputDir.absoluteFilePath("autorun"), QFile::WriteOwner|QFile::ReadOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
#endif
        // stage #2
        if (!errorOcurr)
        {
            ui->publishLog->item(lastIndex)->setIcon(QIcon(":/teacher-web/icons/success.png"));
            ui->publishLog->item(lastIndex)->setFont(ui->publishLog->font());
        }
        ui->publishLog->item(++lastIndex)->setIcon(QIcon(":/teacher-web/icons/current.png"));
        ui->publishLog->item(lastIndex)->setFont(font);
        ui->progressBar->setVisible(false);
        QApplication::processEvents();

        try
        {
            WebsiteDeployWizard* deployWizard = qobject_cast<WebsiteDeployWizard*>(wizard());
            QHash<QString, IProjectDescription*> projectsList = deployWizard->projects();

            ui->progressBar->reset();
            ui->progressBar->setMaximum(projectsList.count() + 1);

            QStringList projectsJSON;
            QStringList projectsReferencesJSON;
            int index = 0;
            foreach(IProjectDescription* description, deployWizard->projects())
            {
                QDir projectDir(description->getProjectLocation());
                if (description->getProjectType().compare("CourseProject") == 0)
                {
                    //Course courseData(description->getProjectLocation());
                    //courseData.loadFromFile(description->getProjectLocation().append("/course-data.xml"));
                    //projectsJSON << "\"" + description->getProjectId() + "\": " + courseData.toJSON();
                }
                else if (description->getProjectType().compare("DiplomaProgramProject") == 0)
                {
                    //DiplomaProgram diplomaProgramData(description->getProjectLocation());
                    //diplomaProgramData.loadFromFile(description->getProjectLocation().append("/program-data.xml"));
                    //projectsJSON << "\"" + description->getProjectId() + "\": " + diplomaProgramData.toJSON();
                }
                else if (description->getProjectType().compare("MasterProgramProject") == 0)
                {
                    //MasterProgram masterProgramData(description->getProjectLocation());
                    //masterProgramData.loadFromFile(description->getProjectLocation().append("/program-data.xml"));
                    //projectsJSON << "\"" + description->getProjectId() + "\": " + masterProgramData.toJSON();
                }
                else if (description->getProjectType().compare("PhDProgramProject") == 0)
                {
                    //PhDProgram phdProgramData(description->getProjectLocation());
                    //phdProgramData.loadFromFile(description->getProjectLocation().append("/program-data.xml"));
                    //projectsJSON << "\"" + description->getProjectId() + "\": " + phdProgramData.toJSON();
                }

                // add dependencies
                QStringList currentProjectReferencesJSON;
                if (!description->referencingProjects().isEmpty())
                {
                    QStringList referencingProjectList;
                    foreach(QString referencingProjectId, description->referencingProjects())
                    {
                        if (projectsList.keys().contains(referencingProjectId))
                        {
                            referencingProjectList.append("\"" + referencingProjectId + "\"");
                        }
                    }

                    if (!referencingProjectList.isEmpty())
                        currentProjectReferencesJSON << "\"referencedBy\": [" + referencingProjectList.join(",") + "]";
                }

                if (!description->referencedProjects().isEmpty())
                {
                    QStringList referencedProjectList;
                    foreach(QString referencedProjectId, description->referencedProjects())
                    {
                        if (projectsList.keys().contains(referencedProjectId))
                        {
                            referencedProjectList.append("\"" + referencedProjectId + "\"");
                        }
                    }

                    if (!referencedProjectList.isEmpty())
                        currentProjectReferencesJSON << "\"referencesTo\": [" + referencedProjectList.join(",") + "]";
                }

                if (!currentProjectReferencesJSON.isEmpty())
                    projectsReferencesJSON << "\"" + description->getProjectId() + "\": {" + currentProjectReferencesJSON.join(",") + "}";

                ui->progressBar->setValue(++index);
            }

            QStringList projectsListJSON;
            projectsListJSON << "{\"projects\": {" + projectsJSON.join(",") + "}";

            if (!projectsReferencesJSON.isEmpty())
                projectsListJSON << ",\"dependencies\": {" + projectsReferencesJSON.join(", ") + "}";
            projectsListJSON << "}";

            QFile outFile(outputDir.absoluteFilePath("html/data/data.json"));
            if (outFile.open(QIODevice::WriteOnly))
            {
                outFile.write(projectsListJSON.join("").toUtf8());
                outFile.close();
            }
            ui->progressBar->setValue(ui->progressBar->maximum());
        }
        catch (...)
        {
            errorOcurr = true;
        }

        // stage #3
        if (!errorOcurr)
        {
            ui->publishLog->item(lastIndex)->setIcon(QIcon(":/teacher-web/icons/success.png"));
            ui->publishLog->item(lastIndex)->setFont(ui->publishLog->font());
        }
        ui->publishLog->item(++lastIndex)->setIcon(QIcon(":/teacher-web/icons/current.png"));
        ui->publishLog->item(lastIndex)->setFont(font);
        ui->progressBar->setVisible(true);
        QApplication::processEvents();

        try
        {
            WebsiteDeployWizard* deployWizard = qobject_cast<WebsiteDeployWizard*>(wizard());

            QStringList filesToBeCopied;
            foreach(IProjectDescription* description, deployWizard->projects())
            {
                QDir projectDir(description->getProjectLocation());
                if (description->getProjectType().compare("CourseProject") == 0)
                {
                    FileSystemUtils::copyDirectory(QDir(description->getProjectLocation()).absoluteFilePath("resources"), outputDir.absoluteFilePath("html/data/resources"), ui->progressBar);
                }
            }
        }
        catch (...)
        {
            errorOcurr = true;
        }


        // stage #4
        if (!errorOcurr)
        {
           ui->publishLog->item(lastIndex)->setIcon(QIcon(":/teacher-web/icons/success.png"));
           ui->publishLog->item(lastIndex)->setFont(ui->publishLog->font());
        }
        ui->publishLog->item(++lastIndex)->setIcon(QIcon(":/teacher-web/icons/current.png"));
        ui->publishLog->item(lastIndex)->setFont(font);
        ui->progressBar->setVisible(true);
        QApplication::processEvents();

        FileSystemUtils::copyDirectory(templatePath, outputDir.absoluteFilePath("html"), ui->progressBar);

        // stage #5
        if (!errorOcurr)
        {
            ui->publishLog->item(lastIndex)->setIcon(QIcon(":/teacher-web/icons/success.png"));
            ui->publishLog->item(lastIndex)->setFont(ui->publishLog->font());
        }
        ui->publishLog->item(++lastIndex)->setIcon(QIcon(":/teacher-web/icons/current.png"));
        ui->publishLog->item(lastIndex)->setFont(font);
        ui->progressBar->setVisible(false);
        QApplication::processEvents();

        // setting entrypoint for template
        QSettings cdAppSettings(outputDir.absoluteFilePath("bin/config.ini"), QSettings::IniFormat);
        cdAppSettings.setValue("title", "Creado con eduWeb 1.0");
        cdAppSettings.setValue("indexFile", TemplateFactory::getInstance()->templates().at(templateIndex).mainFile());
        cdAppSettings.sync();

        // setting template params
        QStringList templateFields = field("templateConfigParams").toStringList();
        if (templateFields.count() > 0)
        {
            QStringList templateConfigParams;
            QStringList paramsTypeFile;


            foreach(QString fieldName, templateFields)
            {
                QString fieldValue = field(fieldName).toString();

                if (fieldName.contains("TypeFile") || fieldName.contains("TypeImage"))
                {
                    paramsTypeFile << fieldValue;

                    if (!fieldValue.isEmpty())
                    {
                        QFileInfo paramFileInfo(fieldValue);
                        fieldValue = paramFileInfo.fileName().prepend("data/templatecfg/");
                    }
                }

                fieldValue.replace('"', "\\\"");
                templateConfigParams << "\t" + fieldName.section('_', -1) + ": \"" + fieldValue.replace('\n', "\\\n") + "\"";
            }

            QStringList templateConfigJSON;
            templateConfigJSON << "{\n" + templateConfigParams.join(", \n") + "\n}\n";

            ui->progressBar->setVisible(true);
            ui->progressBar->reset();
            ui->progressBar->setMaximum(paramsTypeFile.count());
            QApplication::processEvents();

            for(int index = 0; index < paramsTypeFile.count(); index++)
            {
                QFileInfo paramFileInfo(paramsTypeFile.at(index));
                if(!QFile::copy(paramFileInfo.absoluteFilePath(), outputDir.absoluteFilePath(paramFileInfo.fileName().prepend("html/data/templatecfg/"))))
                {
                    ui->publishLog->item(lastIndex)->setIcon(QIcon(":/teacher-web/icons/error.png"));
                    QApplication::processEvents();
                }

                ui->progressBar->setValue(index);
            }

            QFile outFile(outputDir.absoluteFilePath("html/data/config.json"));
            if (outFile.open(QIODevice::WriteOnly))
            {
                outFile.write(templateConfigJSON.join("\n").toUtf8());
                outFile.close();
            }

            ui->progressBar->setValue(ui->progressBar->maximum());
        }

        // finished
        if (!errorOcurr)
        {
           ui->publishLog->item(lastIndex)->setIcon(QIcon(":/teacher-web/icons/success.png"));
           ui->publishLog->item(lastIndex)->setFont(ui->publishLog->font());
        }
        ui->progressBar->setVisible(false);
        QApplication::processEvents();
    }

    published = true;
}
