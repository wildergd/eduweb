#include <QtGui>
#include "settingsmanager.h"
#include "chamilopublishdeployer.h"

QString ChamiloPublishDeployer::pluginName() const
{
	return "ChamiloPublish";
}

QString ChamiloPublishDeployer::pluginDisplayName() const
{
	return trUtf8("Publish to Chamilo");
}

QString ChamiloPublishDeployer::pluginIcon() const
{
	return ":/chamilo-publish-icon.png";
}

QString ChamiloPublishDeployer::group() const
{
    return trUtf8("Learning Management Systems");
}

QString ChamiloPublishDeployer::pluginVersion() const
{
	return "1.0";
}

QString ChamiloPublishDeployer::pluginCompatibilityVersion() const
{
	return "1.2";
}

QString ChamiloPublishDeployer::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString ChamiloPublishDeployer::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString ChamiloPublishDeployer::pluginUrl() const
{
	return "";
}

QString ChamiloPublishDeployer::pluginDescription() const
{
	return "";
}

QString ChamiloPublishDeployer::pluginCopyright() const
{
	return "&copy; 2011" + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString ChamiloPublishDeployer::pluginLicense() const
{
	return "";
}

QStringList ChamiloPublishDeployer::pluginDependencies() const
{
	return QStringList();
}

void ChamiloPublishDeployer::launch(const QList<IProjectDescription*> projects, const QString projectsType, SettingsManager* settings)
{

}

QStringList ChamiloPublishDeployer::getCompatibleProjects() const
{
	QStringList compatibleProjects;
	compatibleProjects << "CourseProject";
	return compatibleProjects;
}

Q_EXPORT_PLUGIN2(chamiloPublishDeployer, ChamiloPublishDeployer)
