#ifndef IPROJECT_H
#define IPROJECT_H

#include "eduweb-core.h"
#include "iplugin.h"
#include "iprojectdescription.h"
#include "settingsmanager.h"

class EDUWEB_CORE_EXPORT IProject: public IPlugin
{
public:
    virtual QString group() const = 0;
    virtual bool launch(IProjectDescription* projectDescription = 0, SettingsManager* settings = 0) = 0;
	virtual bool save() = 0;

signals:
	void projectLoaded();
	void closed();
};

Q_DECLARE_INTERFACE(IProject, "eduweb.core.IProject/1.0")

#endif // IPROJECT_H
