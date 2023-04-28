#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include "template.h"

Template::Template(const QString fileName)
{
	load(fileName);
}

Template::~Template()
{

}

void Template::load(const QString fileName)
{
	QDomDocument descFileData;
	QFile templateDescFile(fileName);
	if (!templateDescFile.open(QFile::ReadOnly | QFile::Text))
		return;

	if (!descFileData.setContent(&templateDescFile))
	{
		templateDescFile.close();
		return;
	}

	// template metadata
	QDomElement templateMetadataElement = descFileData.documentElement().firstChildElement("metadata");

	templateMainFile = (templateMetadataElement.firstChildElement("mainFile").isNull()) ? "index.html" : templateMetadataElement.firstChildElement("mainFile").text();
	templateName = templateMetadataElement.firstChildElement("name").text();
	templateAuthor = templateMetadataElement.firstChildElement("auhtor").text();
	templateDescription = templateMetadataElement.firstChildElement("description").text();

	QFileInfo templateDescFileInfo(templateDescFile);
	templateThumbnailFile = templateMetadataElement.firstChildElement("thumbnail").text();
	if (!templateThumbnailFile.isEmpty())
	{
		templateThumbnailFile = templateDescFileInfo.absoluteDir().absoluteFilePath(templateThumbnailFile);
		templateThumbnail.load(templateThumbnailFile);
	}

	bool ok;
	templateMultiplicity = (templateMetadataElement.firstChildElement("multipleProjects").text().toInt(&ok, 10) == 0) ? Template::SingleProject : Template::MultipleProjects;

	QDomNodeList supportedProjectList = templateMetadataElement.elementsByTagName("projectType");
	if (!supportedProjectList.isEmpty())
	{
		templateSupportedProjects.clear();

		for(int index = 0; index < supportedProjectList.count(); index++)
		{
			QDomElement projectTypeElement = supportedProjectList.at(index).toElement();

			if (!projectTypeElement.isNull())
				templateSupportedProjects.append(projectTypeElement.text());
		}
	}

	// template config params
	QDomElement templateConfigElement = descFileData.documentElement().firstChildElement("configParams");
	if (templateConfigElement.isNull())
		return;

	QDomNodeList templateConfigParamList = templateConfigElement.elementsByTagName("param");
	if (templateConfigParamList.isEmpty())
		return ;

	for(int index = 0; index < templateConfigParamList.count(); index++)
	{
		QDomElement paramElement = templateConfigParamList.at(index).toElement();
		TemplateConfigParam param(paramElement);

		templateConfigParams.append(param);
	}

	templateDescFile.close();
}

QString Template::id() const
{
	return templateID;
}

QString Template::mainFile() const
{
	return templateMainFile;
}

QString Template::name() const
{
	return templateName;
}

QString Template::author() const
{
	return templateAuthor;
}

QString Template::description() const
{
	return templateDescription;
}

Template::TemplateMultiplicity Template::multiplicity() const
{
	return templateMultiplicity;
}

QString Template::screenshotPath() const
{
	return templateThumbnailFile;
}

QPixmap Template::screenshot() const
{
	return QPixmap(templateThumbnail);
}

QStringList Template::supportedProjects() const
{
	return templateSupportedProjects;
}

QList<TemplateConfigParam> Template::configParams() const
{
	return templateConfigParams;
}
