#include <QtGui>
#include "settingsmanager.h"
#include "imscontentpackagedeployer.h"

QString IMSContentPackageDeployer::pluginName() const
{
	return "IMSContentPackageDeployer";
}

QString IMSContentPackageDeployer::pluginDisplayName() const
{
	return trUtf8("IMS Content Package");
}

QString IMSContentPackageDeployer::pluginIcon() const
{
	return ":/ims-content-package-icon.png";
}

QString IMSContentPackageDeployer::group() const
{
    return trUtf8("Content Packages");
}

QString IMSContentPackageDeployer::pluginVersion() const
{
	return "1.0";
}

QString IMSContentPackageDeployer::pluginCompatibilityVersion() const
{
	return "1.2";
}

QString IMSContentPackageDeployer::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString IMSContentPackageDeployer::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString IMSContentPackageDeployer::pluginUrl() const
{
	return "";
}

QString IMSContentPackageDeployer::pluginDescription() const
{
	return "";
}

QString IMSContentPackageDeployer::pluginCopyright() const
{
	return "&copy; 2011" + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString IMSContentPackageDeployer::pluginLicense() const
{
	return "";
}

QStringList IMSContentPackageDeployer::pluginDependencies() const
{
	return QStringList();
}

void IMSContentPackageDeployer::launch(const QList<IProjectDescription*> projects, const QString projectsType, SettingsManager* settings)
{

}

QStringList IMSContentPackageDeployer::getCompatibleProjects() const
{
	QStringList compatibleProjects;
	compatibleProjects << "CourseProject";
	return compatibleProjects;
}

Q_EXPORT_PLUGIN2(imsContentPackageDeployer, IMSContentPackageDeployer)
