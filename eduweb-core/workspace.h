#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "eduweb-core.h"
#include <QHash>
#include <QProgressBar>
#include "iprojectdescription.h"
#include "projectdescription.h"

class EDUWEB_CORE_EXPORT Workspace
{
	friend class ProjectDescription;

public:
	Workspace();
	~Workspace();

	static Workspace* getInstance();
	IProjectDescription* createProject(const QString projectName);
	IProjectDescription* createProjectFromExisting(const QString sourceProject, const QString projectName, QProgressBar * progress = 0);
	IProjectDescription* getProject(const QString projectName);
	void removeProject(const QString projectID, QProgressBar * progress = 0);
	QList<IProjectDescription *> getProjects();
	void load(const QString path);
	void reload();
	QHash<QString, IProjectDescription *> scanFolder(const QString path);
	void exportProject(QString projectID, QString destDir, QProgressBar * progress = 0);
	bool isValidProject(const QString path);
	bool exists(const QString projectID);
	void syncProject(QString projectID, QString sourceFolder, QProgressBar* progress = 0);
	void linkProjects(IProjectDescription* childProject, IProjectDescription* parentProject);
	void unlinkProjects(IProjectDescription* childProject, IProjectDescription* parentProject);
	QString getPath() const;

private:
	QHash<QString, ProjectDescription *> projects;
	QString path;
	QDir workspaceDir;
	static Workspace * singletonInstance;

};

#endif // WORKSPACE_H
