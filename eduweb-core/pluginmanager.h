#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "eduweb-core.h"
#include <QPluginLoader>
#include <QMap>
#include <QHash>
#include "iplugin.h"
#include "ideployer.h"

class EDUWEB_CORE_EXPORT PluginManager
{
public:
    PluginManager();
    ~PluginManager();

    static PluginManager* instance();
    void load(const QString path);
    QHash<QString, IPlugin*> plugins();
    QHash<QString, QObject*> projects();
    QHash<QString, QObject*> deployers();

private:
    QMap<QString, QObject *> pluginsList;
    static PluginManager* singletonInstance;
};

#endif // PLUGINMANAGER_H
