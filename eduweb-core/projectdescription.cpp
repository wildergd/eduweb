#include <QDomDocument>
#include <QTextStream>
#include <QTextCodec>
#include "projectdescription.h"
#include "workspace.h"

ProjectDescription::ProjectDescription(const QString path)
{
	projectPath.setPath(path);

	if (!projectPath.exists("project.xml"))
		save(projectPath.absoluteFilePath("project.xml"));

	load(projectPath.absoluteFilePath("project.xml"));
}

ProjectDescription::~ProjectDescription()
{

}

void ProjectDescription::load(const QString projectFile)
{
	// read project data
	QFile projectDescFile(projectFile);
	if (!projectDescFile.open(QFile::ReadOnly | QFile::Text))
		return;

	if (!projectData.setContent(&projectDescFile))
	{
		projectDescFile.close();
		return;
	}

	projectDescFile.close();
}

void ProjectDescription::save(const QString projectFile)
{
	// read project data
	QFile projectDescFile(projectFile);
	if (!projectDescFile.open(QFile::WriteOnly | QFile::Text))
		return;

	if (projectData.documentElement().tagName().isEmpty())
	{
		QDomElement root = projectData.createElement("project");
		projectData.appendChild(root);

		QDomElement nodeTitle = projectData.createElement("name");
		root.appendChild(nodeTitle);

		QDomText nodeText = projectData.createTextNode("Nuevo projecto");
		nodeTitle.appendChild(nodeText);
	}

	QTextStream stream(&projectDescFile);
	stream.setCodec(QTextCodec::codecForName("UTF-8"));
	projectData.save(stream, 4, QDomNode::EncodingFromTextStream);

	projectDescFile.close();
}

void ProjectDescription::setProjectName( const QString projectName )
{
	QDomNodeList nodes = projectData.documentElement().elementsByTagName("name");
	if (nodes.isEmpty())
		return;
	nodes.at(0).firstChild().setNodeValue(projectName);

	save(projectPath.absoluteFilePath("project.xml"));
}

void ProjectDescription::setProjectType( const QString projectType )
{
	projectData.documentElement().setAttribute("type", projectType);
	save(projectPath.absoluteFilePath("project.xml"));
}

QString ProjectDescription::getProjectId( ) const
{
	return projectPath.dirName();
}

QString ProjectDescription::getProjectName( ) const
{
	QDomNode projectNameElement = projectData.documentElement().firstChild();
	return projectNameElement.firstChild().nodeValue();
}

QString ProjectDescription::getProjectType( ) const
{
	return projectData.documentElement().attribute("type", "");
}

QString ProjectDescription::getProjectLocation( ) const
{
	return projectPath.absolutePath();
}

QDate ProjectDescription::getModifiedDate( ) const
{
	QFileInfo projectFileInfo(projectPath.absoluteFilePath("project.xml"));
	QFileInfo pathInfo(projectPath.absolutePath());

	QDate fileDate = projectFileInfo.lastModified().date();
	QDate dirDate = pathInfo.lastModified().date();

	return (fileDate >= dirDate) ? fileDate : dirDate;
}

QStringList ProjectDescription::referencingProjects()
{
	QDomElement referencingProjectsNode = projectData.documentElement().firstChildElement("referenced_by");
	if (referencingProjectsNode.isNull())
		return QStringList();

	QDomNodeList referencingProjectsList = referencingProjectsNode.elementsByTagName("project");
	if (referencingProjectsList.isEmpty())
		return QStringList();

	QStringList allReferencingProjects;
	for(int index = 0; index < referencingProjectsList.count(); index++)
	{
		QDomElement projectNode = referencingProjectsList.at(index).toElement();
		allReferencingProjects << projectNode.text();
	}

	return allReferencingProjects;
}

QStringList ProjectDescription::referencedProjects()
{
	QDomElement referencedProjectsNode = projectData.documentElement().firstChildElement("references_to");
	if (referencedProjectsNode.isNull())
		return QStringList();

	QDomNodeList referencedProjectsList = referencedProjectsNode.elementsByTagName("project");
	if (referencedProjectsList.isEmpty())
		return QStringList();

	QStringList allReferencedProjects;
	for(int index = 0; index < referencedProjectsList.count(); index++)
	{
		QDomElement projectNode = referencedProjectsList.at(index).toElement();
		allReferencedProjects << projectNode.text();
	}

	return allReferencedProjects;
}

void ProjectDescription::addReferencingProject(const QString projectId)
{
	if (referencingProjects().contains(projectId) || referencedProjects().contains(projectId))
		return ;

	QDomElement referencingProjectsNode = projectData.documentElement().firstChildElement("referenced_by");
	if (referencingProjectsNode.isNull())
	{
		referencingProjectsNode = projectData.createElement("referenced_by");
		projectData.documentElement().appendChild(referencingProjectsNode);
	}

	QDomElement nodeReferencingProject = projectData.createElement("project");
	referencingProjectsNode.appendChild(nodeReferencingProject);

	QDomText nodeProjectId = projectData.createTextNode(projectId);
	nodeReferencingProject.appendChild(nodeProjectId);

	save(projectPath.absoluteFilePath("project.xml"));
}

void ProjectDescription::removeReferencingProject(const QString projectId)
{
	QStringList allReferencingProjects = referencingProjects();
	if (!allReferencingProjects.contains(projectId))
		return ;

	QDomElement referencingProjectsNode = projectData.documentElement().firstChildElement("referenced_by");
	if (referencingProjectsNode.isNull())
		return ;

	QDomNodeList referencingProjectsList = referencingProjectsNode.elementsByTagName("project");
	if (referencingProjectsList.isEmpty())
		return ;

	int index = allReferencingProjects.toVector().indexOf(projectId);
	QDomElement projectNode = referencingProjectsList.at(index).toElement();
	referencingProjectsNode.removeChild(projectNode);
	allReferencingProjects.removeAll(projectId);

	if (allReferencingProjects.isEmpty())
		projectData.documentElement().removeChild(referencingProjectsNode);

	save(projectPath.absoluteFilePath("project.xml"));
}

void ProjectDescription::addReferencedProject(const QString projectId)
{
	if (referencingProjects().contains(projectId) || referencedProjects().contains(projectId))
		return ;

	QDomElement referencedProjectsNode = projectData.documentElement().firstChildElement("references_to");
	if (referencedProjectsNode.isNull())
	{
		referencedProjectsNode = projectData.createElement("references_to");
		projectData.documentElement().appendChild(referencedProjectsNode);
	}

	QDomElement nodeReferencedProject = projectData.createElement("project");
	referencedProjectsNode.appendChild(nodeReferencedProject);

	QDomText nodeProjectId = projectData.createTextNode(projectId);
	nodeReferencedProject.appendChild(nodeProjectId);

	save(projectPath.absoluteFilePath("project.xml"));
}

void ProjectDescription::removeReferencedProject(const QString projectId)
{
	QStringList allReferencedProjects = referencedProjects();
	if (!allReferencedProjects.contains(projectId))
		return ;

	QDomElement referencedProjectsNode = projectData.documentElement().firstChildElement("references_to");
	if (referencedProjectsNode.isNull())
		return ;

	QDomNodeList referencedProjectsList = referencedProjectsNode.elementsByTagName("project");
	if (referencedProjectsList.isEmpty())
		return ;

	int index = allReferencedProjects.toVector().indexOf(projectId);
	QDomElement projectNode = referencedProjectsList.at(index).toElement();
	referencedProjectsNode.removeChild(projectNode);
	allReferencedProjects.removeAll(projectId);

	if (allReferencedProjects.isEmpty())
		projectData.documentElement().removeChild(referencedProjectsNode);

	save(projectPath.absoluteFilePath("project.xml"));
}
