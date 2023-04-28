#ifndef IPROJECTCONTAINER_H
#define IPROJECTCONTAINER_H

#include "eduweb-core.h"
#include "iproject.h"

class EDUWEB_CORE_EXPORT IProjectContainer
{
public:
	virtual QStringList projectsCanLink() = 0;
};

Q_DECLARE_INTERFACE(IProjectContainer, "eduweb.core.IProjectContainer/1.0")

#endif // IPROJECTCONTAINER_H
