#ifndef CHAMILOPUBLISHDEPLOYER_H
#define CHAMILOPUBLISHDEPLOYER_H

#include <QStringList>
#include "iplugin.h"
#include "ideployer.h"
#include "iprojectdescription.h"

class ChamiloPublishDeployer: public QObject, public IDeployer
{
	Q_OBJECT
	Q_INTERFACES(IDeployer IPlugin)
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
    void launch(const QList<IProjectDescription*> projects, const QString projectsType = "", SettingsManager* settings = 0);
	QStringList getCompatibleProjects() const;
};

#endif // CHAMILOPUBLISHDEPLOYER_H
