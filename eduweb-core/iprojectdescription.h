#ifndef IPROJECTDESCRIPTION_H
#define IPROJECTDESCRIPTION_H

#include "eduweb-core.h"
#include <QDate>

class QDate;
//class IProject;

class EDUWEB_CORE_EXPORT IProjectDescription
{
public:
	virtual QString getProjectId( ) const = 0;
	virtual QString getProjectName( ) const = 0;
	virtual QString getProjectType( ) const = 0;
	virtual QString getProjectLocation( ) const = 0;
	virtual QDate getModifiedDate( ) const = 0;
	virtual QStringList referencedProjects( ) = 0;
	virtual QStringList referencingProjects( ) = 0;
	virtual void setProjectName( const QString projectName ) = 0;
	virtual void setProjectType( const QString projectType ) = 0;
};

Q_DECLARE_INTERFACE(IProjectDescription, "eduweb.core.IProjectDescription/1.0")

#endif // IPROJECTDESCRIPTION_H
