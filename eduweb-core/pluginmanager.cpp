#include <QtDebug>
#include <QDir>
#include <QApplication>
#include <assert.h>
#include "pluginmanager.h"
#include "ideployer.h"
#include "iproject.h"

PluginManager * PluginManager::singletonInstance = NULL;

PluginManager::PluginManager()
{
    assert(!singletonInstance);
    singletonInstance = this;
}

PluginManager::~PluginManager()
{
    assert(singletonInstance);
    singletonInstance = NULL;
}

PluginManager* PluginManager::instance()
{
    return singletonInstance;
}

void PluginManager::load(const QString path)
{
    QDir pluginDir(path);

    if (QDir::isRelativePath(path))
            pluginDir.setPath(QDir(QApplication::applicationDirPath()).absoluteFilePath(path));

    if (!pluginDir.exists())
            return;

    foreach (QString fileName, pluginDir.entryList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot, QDir::DirsFirst))
    {
        QFileInfo info(pluginDir.absoluteFilePath(fileName));
        if (info.isFile())
        {
            QPluginLoader loader(info.absoluteFilePath());
            QObject* pluginObject = loader.instance();
            if (IPlugin* plugin = qobject_cast<IPlugin*>(pluginObject))
            {
                plugin->_pluginFileName = info.fileName();
                plugin->_pluginPath = info.absolutePath();
                pluginsList.insert(plugin->pluginName(), pluginObject);
            }
        }
        else if (info.isDir())
        {
            load(info.absoluteFilePath());
        }
    }
}

QHash<QString, IPlugin*> PluginManager::plugins()
{
    if (pluginsList.isEmpty())
            return QHash<QString, IPlugin*>();

    QHash<QString, IPlugin*> allPlugins;

    foreach(QObject* plugin, pluginsList)
    {
        if (IPlugin* pluginInfo = qobject_cast<IPlugin*>(plugin))
            allPlugins.insert(pluginInfo->pluginName(), pluginInfo);
    }

    return allPlugins;
}

QHash<QString, QObject*> PluginManager::projects()
{
    if (pluginsList.isEmpty())
        return QHash<QString, QObject*>();

    QHash<QString, QObject*> allProjects;

    foreach(QObject* plugin, pluginsList)
    {
        if (IProject* project = qobject_cast<IProject*>(plugin))
            allProjects.insert(project->pluginName(), plugin);
    }

    return allProjects;
}

QHash<QString, QObject*> PluginManager::deployers()
{
    if (pluginsList.isEmpty())
        return QHash<QString, QObject*>();

    QHash<QString, QObject*> allDeployers;

    foreach(QObject* plugin, pluginsList)
    {
        if (IDeployer* deployer = qobject_cast<IDeployer*>(plugin))
            allDeployers.insert(deployer->pluginName(), plugin);
    }

    return allDeployers;
}

static PluginManager pluginManager;
