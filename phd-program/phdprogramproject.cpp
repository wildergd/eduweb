#include <QtGui>
#include "PhDProgramProject.h"

//void (*PhDProgram::initFunc)(PhDProgram*) = PhDProgramProject::createDefaults;

QString PhDProgramProject::pluginName() const
{
	return "PhDProgramProject";
}

QString PhDProgramProject::pluginDisplayName() const
{
	return trUtf8("PhD Program");
}

QString PhDProgramProject::group() const 
{
	return trUtf8("Postgraduate Education");
}

QString PhDProgramProject::pluginIcon() const
{
	return ":/phd-program-icon.png";
}

QString PhDProgramProject::pluginVersion() const
{
	return "1.1";
}

QString PhDProgramProject::pluginCompatibilityVersion() const
{
	return "1.0";
}

QString PhDProgramProject::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString PhDProgramProject::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString PhDProgramProject::pluginUrl() const
{
	return "";
}

QString PhDProgramProject::pluginDescription() const
{
	return "";
}

QString PhDProgramProject::pluginCopyright() const
{
	return "&copy; 2011 " + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString PhDProgramProject::pluginLicense() const
{
	return "";
}

QStringList PhDProgramProject::pluginDependencies() const
{
	QStringList dependencies;
//	dependencies << "CourseProject";
	return dependencies;
}
QStringList PhDProgramProject::projectsCanLink()
{
	QStringList referencedProjects;
	referencedProjects << "CourseProject";
	referencedProjects << "DiplomaProgramProject";
	return referencedProjects;
}

void PhDProgramProject::launchConfig(SettingsManager* settings)
{
}

bool PhDProgramProject::launch(IProjectDescription * projectDescription, SettingsManager* settings)
{
	return true;
}

bool PhDProgramProject::save()
{
	return true;
}

/*void PhDProgramProject::createDefaults(PhDProgram * phdProgram)
{
}*/

Q_EXPORT_PLUGIN2(phdProgramProject, PhDProgramProject)
