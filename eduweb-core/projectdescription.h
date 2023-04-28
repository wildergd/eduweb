#ifndef PROJECTDESCRIPTION_H
#define PROJECTDESCRIPTION_H

#include "eduweb-core.h"
#include <QDir>
#include <QDomDocument>
#include "iprojectdescription.h"

class Workspace;

class EDUWEB_CORE_EXPORT ProjectDescription: public IProjectDescription
{
	friend class Workspace;
public:
	ProjectDescription(const QString projectPath);
	~ProjectDescription();

	QString getProjectId() const;
	QString getProjectType() const;
	QString getProjectName() const;
	QString getProjectLocation() const;
	QDate getModifiedDate() const;
	QStringList referencedProjects();
	QStringList referencingProjects();

	void setProjectName(const QString projectName);
	void setProjectType(const QString projectType);
	void addReferencingProject(const QString projectId);
	void removeReferencingProject(const QString projectId);
	void addReferencedProject(const QString projectId);
	void removeReferencedProject(const QString projectId);

private:
	QDir projectPath;
	QDomDocument projectData;

	void load(const QString projectFile);
	void save(const QString projectFile);

};

#endif // PROJECTDESCRIPTION_H
