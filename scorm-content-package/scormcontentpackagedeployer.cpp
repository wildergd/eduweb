#include <QtGui>
#include "settingsmanager.h"
#include "scormcontentpackagedeployer.h"

QString SCORMContentPackageDeployer::pluginName() const
{
	return "SCORMContentPackageDeployer";
}

QString SCORMContentPackageDeployer::pluginDisplayName() const
{
	return trUtf8("SCORM Content Package");
}

QString SCORMContentPackageDeployer::pluginIcon() const
{
	return ":/scorm-content-package-icon.png";
}

QString SCORMContentPackageDeployer::group() const
{
    return trUtf8("Content Packages");
}

QString SCORMContentPackageDeployer::pluginVersion() const
{
	return "1.0";
}

QString SCORMContentPackageDeployer::pluginCompatibilityVersion() const
{
	return "1.2";
}

QString SCORMContentPackageDeployer::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString SCORMContentPackageDeployer::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString SCORMContentPackageDeployer::pluginUrl() const
{
	return "";
}

QString SCORMContentPackageDeployer::pluginDescription() const
{
	return "";
}

QString SCORMContentPackageDeployer::pluginCopyright() const
{
	return "&copy; 2011" + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString SCORMContentPackageDeployer::pluginLicense() const
{
	return "";
}

QStringList SCORMContentPackageDeployer::pluginDependencies() const
{
	return QStringList();
}

void SCORMContentPackageDeployer::launch(const QList<IProjectDescription*> projects, const QString projectsType, SettingsManager* settings)
{

}

QStringList SCORMContentPackageDeployer::getCompatibleProjects() const
{
	QStringList compatibleProjects;
	compatibleProjects << "CourseProject";
	return compatibleProjects;
}

Q_EXPORT_PLUGIN2(scormContentPackageDeployer, SCORMContentPackageDeployer)
