#ifndef IDEPLOYER_H
#define IDEPLOYER_H

#include "eduweb-core.h"
#include <QHash>
#include "iplugin.h"
#include "iproject.h"
#include "iprojectdescription.h"
#include "settingsmanager.h"

class EDUWEB_CORE_EXPORT IDeployer: public IPlugin
{
public:
    virtual QString group() const = 0;
    virtual void launch(QList<IProjectDescription*> projects, const QString projectsType = "", SettingsManager* settings = 0) = 0;
	virtual QStringList getCompatibleProjects() const = 0;
};

Q_DECLARE_INTERFACE(IDeployer, "eduweb.core.IDeployer/1.0")

#endif // IDEPLOYER_H
