#include <QtGui>
#include "DiplomaProgramProject.h"

//void (*DiplomaProgram::initFunc)(DiplomaProgram*) = DiplomaProgramProject::createDefaults;

QString DiplomaProgramProject::pluginName() const
{
	return "DiplomaProgramProject";
}

QString DiplomaProgramProject::pluginDisplayName() const
{
	return trUtf8("Diploma Program");
}

QString DiplomaProgramProject::group() const 
{
    return trUtf8("Postgraduate Education");
}

QString DiplomaProgramProject::pluginIcon() const
{
	return ":/diploma-program-icon.png";
}

QString DiplomaProgramProject::pluginVersion() const
{
	return "1.1";
}

QString DiplomaProgramProject::pluginCompatibilityVersion() const
{
	return "1.0";
}

QString DiplomaProgramProject::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString DiplomaProgramProject::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString DiplomaProgramProject::pluginUrl() const
{
	return "";
}

QString DiplomaProgramProject::pluginDescription() const
{
	return "";
}

QString DiplomaProgramProject::pluginCopyright() const
{
	return "&copy; 2011 " + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString DiplomaProgramProject::pluginLicense() const
{
	return "";
}

QStringList DiplomaProgramProject::pluginDependencies() const
{
	QStringList dependencies;
//	dependencies << "CourseProject";
	return dependencies;
}
QStringList DiplomaProgramProject::projectsCanLink()
{
	QStringList referencedProjects;
	referencedProjects << "CourseProject";
	return referencedProjects;
}

QStringList DiplomaProgramProject::projectsCanBeLinkedTo()
{
	QStringList referencingProjects;
	referencingProjects << "MasterProgramProject";
	referencingProjects << "PhDProgramProject";
	return referencingProjects;
}

void DiplomaProgramProject::launchConfig(SettingsManager* settings)
{
}

bool DiplomaProgramProject::launch(IProjectDescription * projectDescription, SettingsManager* settings)
{
	return true;
}

bool DiplomaProgramProject::save()
{
	return true;
}

/*void DiplomaProgramProject::createDefaults(DiplomaProgram * diploma)
{
}*/

Q_EXPORT_PLUGIN2(diplomaProgramProject, DiplomaProgramProject)
