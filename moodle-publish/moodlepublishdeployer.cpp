#include <QtGui>
#include "settingsmanager.h"
#include "moodlepublishdeployer.h"

QString MoodlePublishDeployer::pluginName() const
{
	return "MoodlePublish";
}

QString MoodlePublishDeployer::pluginDisplayName() const
{
	return trUtf8("Publish to Moodle");
}

QString MoodlePublishDeployer::pluginIcon() const
{
	return ":/moodle-publish-icon.png";
}

QString MoodlePublishDeployer::group() const
{
    return trUtf8("Learning Management Systems");
}

QString MoodlePublishDeployer::pluginVersion() const
{
	return "1.0";
}

QString MoodlePublishDeployer::pluginCompatibilityVersion() const
{
	return "1.2";
}

QString MoodlePublishDeployer::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString MoodlePublishDeployer::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString MoodlePublishDeployer::pluginUrl() const
{
	return "";
}

QString MoodlePublishDeployer::pluginDescription() const
{
	return "";
}

QString MoodlePublishDeployer::pluginCopyright() const
{
	return "&copy; 2011" + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString MoodlePublishDeployer::pluginLicense() const
{
	return "";
}

QStringList MoodlePublishDeployer::pluginDependencies() const
{
	return QStringList();
}

void MoodlePublishDeployer::launch(const QList<IProjectDescription*> projects, const QString projectsType, SettingsManager* settings)
{

}

QStringList MoodlePublishDeployer::getCompatibleProjects() const
{
	QStringList compatibleProjects;
	compatibleProjects << "CourseProject";
	return compatibleProjects;
}

Q_EXPORT_PLUGIN2(moodlePublishDeployer, MoodlePublishDeployer)
