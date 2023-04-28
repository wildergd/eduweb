#include <QtGui>
#include "settingsmanager.h"
#include "educationalwebsitedeployer.h"
#include "templatefactory.h"
#include "websitedeploywizard.h"
#include "iprojectdescription.h"

QString EducationalWebsiteDeployer::pluginName() const
{
	return "EducationalWebsiteDeployer";
}

QString EducationalWebsiteDeployer::pluginDisplayName() const
{
	return trUtf8("Educational Website");
}

QString EducationalWebsiteDeployer::pluginIcon() const
{
	return ":/educational-website-icon.png";
}

QString EducationalWebsiteDeployer::group() const
{
    return trUtf8("Multimedia CD-ROM & Educational Web Pages");
}

QString EducationalWebsiteDeployer::pluginVersion() const
{
	return "1.1";
}

QString EducationalWebsiteDeployer::pluginCompatibilityVersion() const
{
	return "1.2";
}

QString EducationalWebsiteDeployer::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString EducationalWebsiteDeployer::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString EducationalWebsiteDeployer::pluginUrl() const
{
	return "";
}

QString EducationalWebsiteDeployer::pluginDescription() const
{
	return "";
}

QString EducationalWebsiteDeployer::pluginCopyright() const
{
	return "&copy; 2011" + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString EducationalWebsiteDeployer::pluginLicense() const
{
    return "";
}

QStringList EducationalWebsiteDeployer::pluginDependencies() const
{
	return QStringList();
}

void EducationalWebsiteDeployer::launch(QList<IProjectDescription*> projects, const QString projectsType, SettingsManager* settings)
{
    int projectsCount = 0;
	foreach(IProjectDescription* project, projects)
	{
		if (project->getProjectType().compare(projectsType) == 0)
			projectsCount++;
    }

    TemplateFactory::getInstance()->setFilter(projectsType, (projectsCount > 1) ? Template::MultipleProjects : Template::SingleProject);

    WebsiteDeployWizard wizard;
    wizard.setProjects(projects);
    wizard.exec();
}

QStringList EducationalWebsiteDeployer::getCompatibleProjects() const
{
	QStringList compatibleProjects;
	compatibleProjects << "CourseProject";
	compatibleProjects << "DiplomaProgramProject";
	compatibleProjects << "MasterProgramProject";
	compatibleProjects << "PhDProgramProject";
	return compatibleProjects;
}


Q_EXPORT_PLUGIN2(educationalWebsiteDeployer, EducationalWebsiteDeployer)
