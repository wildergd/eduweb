#include <QtGui>
#include "settingsmanager.h"
#include "dokeospublishdeployer.h"

QString DokeosPublishDeployer::pluginName() const
{
	return "DokeosPublish";
}

QString DokeosPublishDeployer::pluginDisplayName() const
{
	return trUtf8("Publish to Dokeos");
}

QString DokeosPublishDeployer::pluginIcon() const
{
	return ":/dokeos-publish-icon.png";
}

QString DokeosPublishDeployer::group() const
{
    return trUtf8("Learning Management Systems");
}

QString DokeosPublishDeployer::pluginVersion() const
{
	return "1.0";
}

QString DokeosPublishDeployer::pluginCompatibilityVersion() const
{
	return "1.2";
}

QString DokeosPublishDeployer::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString DokeosPublishDeployer::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString DokeosPublishDeployer::pluginUrl() const
{
	return "";
}

QString DokeosPublishDeployer::pluginDescription() const
{
	return "";
}

QString DokeosPublishDeployer::pluginCopyright() const
{
	return "&copy; 2011" + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString DokeosPublishDeployer::pluginLicense() const
{
	return "";
}

QStringList DokeosPublishDeployer::pluginDependencies() const
{
	return QStringList();
}

void DokeosPublishDeployer::launch(const QList<IProjectDescription*> projects, const QString projectsType, SettingsManager* settings)
{

}

QStringList DokeosPublishDeployer::getCompatibleProjects() const
{
	QStringList compatibleProjects;
	compatibleProjects << "CourseProject";
	return compatibleProjects;
}

Q_EXPORT_PLUGIN2(dokeosPublishDeployer, DokeosPublishDeployer)
