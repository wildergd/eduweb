#include <QtGui>
#include "masterprogramproject.h"

//void (*MasterProgram::initFunc)(MasterProgram*) = MasterProgramProject::createDefaults;

QString MasterProgramProject::pluginName() const
{
	return "MasterProgramProject";
}

QString MasterProgramProject::pluginDisplayName() const
{
	return trUtf8("Master Program");
}

QString MasterProgramProject::group() const 
{
	return trUtf8("Postgraduate Education");
}

QString MasterProgramProject::pluginIcon() const
{
	return ":/master-program-icon.png";
}

QString MasterProgramProject::pluginVersion() const
{
	return "1.1";
}

QString MasterProgramProject::pluginCompatibilityVersion() const
{
	return "1.0";
}

QString MasterProgramProject::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString MasterProgramProject::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString MasterProgramProject::pluginUrl() const
{
	return "";
}

QString MasterProgramProject::pluginDescription() const
{
	return "";
}

QString MasterProgramProject::pluginCopyright() const
{
	return "&copy; 2011 " + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString MasterProgramProject::pluginLicense() const
{
	return "";
}

QStringList MasterProgramProject::pluginDependencies() const
{
	QStringList dependencies;
//	dependencies << "CourseProject";
	return dependencies;
}
QStringList MasterProgramProject::projectsCanLink()
{
	QStringList referencedProjects;
	referencedProjects << "CourseProject";
	referencedProjects << "DiplomaProgramProject";
	return referencedProjects;
}

void MasterProgramProject::launchConfig(SettingsManager* settings)
{
}

bool MasterProgramProject::launch(IProjectDescription * projectDescription, SettingsManager* settings)
{
	return true;
}

bool MasterProgramProject::save()
{
	return true;
}

/*void MasterProgramProject::createDefaults(MasterProgram * masterProgram)
{
}*/

Q_EXPORT_PLUGIN2(masterProgramProject, MasterProgramProject)
