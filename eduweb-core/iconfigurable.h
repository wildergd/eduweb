#ifndef ICONFIGURABLE_H
#define ICONFIGURABLE_H

#include "eduweb-core.h"
#include "settingsmanager.h"

class EDUWEB_CORE_EXPORT IConfigurable
{
public:
	virtual void launchConfig(SettingsManager* settings) = 0;
};

Q_DECLARE_INTERFACE(IConfigurable, "eduweb.core.IConfigurable/1.0")

#endif // ICONFIGURABLE_H
