#include <QtDebug>
#include <QUuid>
#include <QProgressBar>
#include <assert.h>
#include "workspace.h"
#include "filesystemutils.h"

Workspace * Workspace::singletonInstance = NULL;

Workspace::Workspace()
{
    assert(!singletonInstance);
    singletonInstance = this;
}

Workspace::~Workspace()
{
    assert(singletonInstance);
    singletonInstance = NULL;
}

Workspace * Workspace::getInstance()
{
    return singletonInstance;
}

QString Workspace::getPath() const
{
    return path;
}

IProjectDescription* Workspace::createProject(const QString projectName)
{
    QString projectID = QUuid::createUuid();

    if (workspaceDir.exists(projectID))
        return 0;

    if (!workspaceDir.mkdir(projectID))
        return 0;

    ProjectDescription * description = new ProjectDescription(workspaceDir.absoluteFilePath(projectID));
    description->setProjectName(projectName);

    projects.insert(projectID, description);

    return description;
}

IProjectDescription* Workspace::createProjectFromExisting(const QString sourceProject, const QString projectName, QProgressBar * progress)
{
    QString projectID = QUuid::createUuid();

    while(workspaceDir.exists(projectID))
        projectID = QUuid::createUuid();

    if (!workspaceDir.mkdir(projectID))
        return 0;

    //copy source project content
    if (!FileSystemUtils::copyDirectory(workspaceDir.absoluteFilePath(sourceProject), workspaceDir.absoluteFilePath(projectID), progress))
        return 0;

    ProjectDescription * description = new ProjectDescription(workspaceDir.absoluteFilePath(projectID));
    description->setProjectName(projectName);

    projects.insert(projectID, description);

    return description;
}

bool Workspace::exists(const QString projectID)
{
    return projects.contains(projectID);
}

bool Workspace::isValidProject(const QString path)
{
    QFileInfo info(path);
    QDir projectPath(path);
    QString id = info.fileName();
    return !QUuid(id).isNull() && projectPath.exists("project.xml");
}

IProjectDescription* Workspace::getProject(const QString projectName)
{
    if (!projects.contains(projectName) || !isValidProject(workspaceDir.absoluteFilePath(projectName)))
        return NULL;

    ProjectDescription * projectInfo = projects.value(projectName);
    return projectInfo;
}

QList<IProjectDescription *> Workspace::getProjects()
{
    QList<IProjectDescription *> projectsList;

    if (!projects.empty())
    {
        foreach(ProjectDescription * projectInfo, projects)
        {
            projectsList.append(projectInfo);
        }
    }

    return projectsList;
}

void Workspace::load(const QString path)
{
    QDir projectsDir(path);

    if (!projectsDir.exists())
        return;

    workspaceDir.setPath(path);
    projects.clear();

    foreach (QString dirName, projectsDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot|QDir::Readable))
    {
        QFileInfo info(projectsDir.absoluteFilePath(dirName));
        if (info.isDir() && isValidProject(info.absoluteFilePath()))
        {
            ProjectDescription * projectDescription = new ProjectDescription(info.absoluteFilePath());
            projects.insert(dirName, projectDescription);
        }
    }
}

void Workspace::reload()
{
    load(workspaceDir.absolutePath());
}

QHash<QString, IProjectDescription*> Workspace::scanFolder(const QString path)
{
    QDir sourceDir(path);
    if (!sourceDir.exists())
        return QHash<QString, IProjectDescription*>();

    QHash<QString, IProjectDescription*> existingProjects;

    foreach (QString dirName, sourceDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot|QDir::Readable))
    {
        QFileInfo info(sourceDir.absoluteFilePath(dirName));
        if (info.isDir() && isValidProject(info.absoluteFilePath()))
        {
            ProjectDescription * projectDescription = new ProjectDescription(info.absoluteFilePath());
            existingProjects.insert(projectDescription->getProjectId(), projectDescription);
        }
    }

    return existingProjects;
}

void Workspace::exportProject(QString projectID, QString destDir, QProgressBar * progress)
{
    if (!workspaceDir.exists(projectID))
        return ;

    QDir dest(destDir);
    if (!dest.mkdir(projectID))
        return ;

    if (!FileSystemUtils::copyDirectory(workspaceDir.absoluteFilePath(projectID), dest.absoluteFilePath(projectID), progress))
        return ;
}

void Workspace::removeProject(const QString projectID, QProgressBar * progress)
{
    if (!workspaceDir.exists(projectID))
        return ;

    ProjectDescription* projectInfo = projects.value(projectID);
    if (!projectInfo->referencingProjects().isEmpty())
    {
        foreach(QString referencingProjectID, projectInfo->referencingProjects())
        {
            IProjectDescription* referencingProjectInfo = getProject(referencingProjectID);
            unlinkProjects(projectInfo, referencingProjectInfo);
        }
    }

    if (!projectInfo->referencedProjects().isEmpty())
    {
        foreach(QString referencedProjectID, projectInfo->referencedProjects())
        {
            IProjectDescription* referencedProjectInfo = getProject(referencedProjectID);
            unlinkProjects(referencedProjectInfo, projectInfo);
        }
    }

    if (!FileSystemUtils::removeDirectory(workspaceDir.absoluteFilePath(projectID), progress))
        return ;

    projects.remove(projectID);
}

void Workspace::syncProject(QString projectID, QString sourceFolder, QProgressBar* progress)
{
    if(IProjectDescription * project = Workspace::getInstance()->getProject(projectID))
    {
        QDir sourceDir(sourceFolder);
        QDir destDir(project->getProjectLocation());

        QSet<QString> filesInWorkSpace = FileSystemUtils::scanFolder(destDir.absolutePath(), destDir.absolutePath()).toSet();
        QSet<QString> filesInFolder = FileSystemUtils::scanFolder(sourceDir.absolutePath(), sourceDir.absolutePath()).toSet();

        QStringList filesToBeUpdated = QStringList((filesInWorkSpace & filesInFolder).toList()); // project.xml is contained here
        QStringList filesToBeDeleted = QStringList((filesInWorkSpace - filesInFolder).toList());
        QStringList filesToBeCopied = QStringList((filesInFolder - filesInWorkSpace).toList());

        qStableSort(filesToBeUpdated.begin(), filesToBeUpdated.end(), qGreater<QString>());
        qStableSort(filesToBeDeleted.begin(), filesToBeDeleted.end(), qGreater<QString>());
        qStableSort(filesToBeCopied.begin(), filesToBeCopied.end(), qGreater<QString>());

        if (progress)
        {
            progress->reset();
            progress->setMaximum((filesInFolder + filesInWorkSpace).count() - 1);
        }

        foreach(QString fileName, filesToBeCopied)
        {
            QFileInfo fileInfo(fileName);
            if (!destDir.exists(fileInfo.path()))
                destDir.mkpath(fileInfo.path());

            if (QFileInfo(sourceDir.absoluteFilePath(fileInfo.filePath())).isFile())
                QFile::copy(sourceDir.absoluteFilePath(fileName), destDir.absoluteFilePath(fileInfo.filePath()));

            if (progress)
                progress->setValue(progress->value() + 1);
        }

        filesToBeUpdated.removeAll("project.xml");
        foreach(QString fileName, filesToBeUpdated)
        {
            QFileInfo fileInfo(fileName);
            if (QFileInfo(sourceDir.absoluteFilePath(fileInfo.filePath())).isFile())
            {
                QString srcMD5 = FileSystemUtils::hashMD5(sourceDir.absoluteFilePath(fileInfo.filePath()));
                QString dstMD5 = FileSystemUtils::hashMD5(destDir.absoluteFilePath(fileInfo.filePath()));

                if (srcMD5 != dstMD5)
                {
                    QFile(destDir.absoluteFilePath(fileInfo.filePath())).remove();
                    QFile::copy(sourceDir.absoluteFilePath(fileName), destDir.absoluteFilePath(fileInfo.filePath()));
                }
            }

            if (progress)
                progress->setValue(progress->value() + 1);
        }

        foreach(QString fileName, filesToBeDeleted)
        {
            QFileInfo fileInfo(destDir.absoluteFilePath(fileName));
            if(fileInfo.exists() && fileInfo.isFile())
                destDir.remove(fileName);
            else if(fileInfo.isDir())
                fileInfo.dir().rmpath(fileInfo.fileName());

            if (progress)
                progress->setValue(progress->value() + 1);
        }
    }

    reload();
}

void Workspace::linkProjects(IProjectDescription* childProject, IProjectDescription* parentProject)
{
    ProjectDescription* childProjectInfo = projects.value(childProject->getProjectId());
    ProjectDescription* parentProjectInfo = projects.value(parentProject->getProjectId());

    // add child reference to parent
    parentProjectInfo->addReferencedProject(childProject->getProjectId());

    // add parent reference to child
    childProjectInfo->addReferencingProject(parentProject->getProjectId());
}

void Workspace::unlinkProjects(IProjectDescription* childProject, IProjectDescription* parentProject)
{
    ProjectDescription* childProjectInfo = projects.value(childProject->getProjectId());
    ProjectDescription* parentProjectInfo = projects.value(parentProject->getProjectId());

    // add child reference to parent
    parentProjectInfo->removeReferencedProject(childProject->getProjectId());

    // add parent reference to child
    childProjectInfo->removeReferencingProject(parentProject->getProjectId());
}

static Workspace workspace;
