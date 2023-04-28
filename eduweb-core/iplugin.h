#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "eduweb-core.h"
//#include "pluginmanager.h"

class PluginManager;

class EDUWEB_CORE_EXPORT IPlugin
{
        friend class PluginManager;
public:
	virtual QString pluginName() const = 0;
	virtual QString pluginDisplayName() const = 0;
	virtual QString pluginIcon() const = 0;
	virtual QString pluginVersion() const = 0;
	virtual QString pluginCompatibilityVersion() const = 0;
	virtual QString pluginAuthor() const = 0;
	virtual QString pluginVendor() const = 0;
	virtual QString pluginUrl() const = 0;
	virtual QString pluginDescription() const = 0;
	virtual QString pluginCopyright() const = 0;
	virtual QString pluginLicense() const = 0;
	virtual QStringList pluginDependencies() const = 0;

        QString pluginFileName() { return _pluginFileName; }
        QString pluginFolder() { return _pluginPath; }

protected:
        QString _pluginFileName;
        QString _pluginPath;
};

Q_DECLARE_INTERFACE(IPlugin, "eduweb.core.IPlugin/1.0")

#endif // IPLUGIN_H
