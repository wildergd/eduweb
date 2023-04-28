#ifndef IPROJECTCANBECONTAINED_H
#define IPROJECTCANBECONTAINED_H

#include"eduweb-core.h"

class EDUWEB_CORE_EXPORT IProjectCanBeContained
{
public:
	virtual QStringList projectsCanBeLinkedTo() = 0;
};

Q_DECLARE_INTERFACE(IProjectCanBeContained, "eduweb.core.IProjectCanBeContained/1.0")

#endif // IPROJECTCANBECONTAINED_H
