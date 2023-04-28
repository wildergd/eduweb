#ifndef DIPLOMAPROGRAMPROJECT_H
#define DIPLOMAPROGRAMPROJECT_H

#include <QObject>
#include <QStringList>
#include "iplugin.h"
#include "iproject.h"
#include "iprojectcanbecontained.h"
#include "iprojectcontainer.h"
#include "iprojectdescription.h"
#include "iconfigurable.h"

class DiplomaProgramProject: public QObject, public IProject, public IProjectCanBeContained, public IProjectContainer, public IConfigurable
{
	Q_OBJECT
    Q_INTERFACES(IProject IPlugin IProjectCanBeContained IProjectContainer IConfigurable)
public:
	QString pluginName() const;
	QString pluginDisplayName() const;
	QString pluginIcon() const;
	QString pluginVersion() const;
	QString pluginCompatibilityVersion() const;
	QString pluginAuthor() const;
	QString pluginVendor() const;
	QString pluginUrl() const;
	QString pluginDescription() const;
	QString pluginCopyright() const;
	QString pluginLicense() const;
	QStringList pluginDependencies() const;
    QString group() const;
    bool launch(IProjectDescription * projectDescription = 0, SettingsManager* settings = 0);
	bool save();

	QStringList projectsCanLink();
	QStringList projectsCanBeLinkedTo();
	
	void launchConfig(SettingsManager* settings);

	//static void createDefaults(DiplomaProgram * diploma);

private:	
	static SettingsManager* settings;
};

#endif
