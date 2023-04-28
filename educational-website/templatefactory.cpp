#include <QDir>
#include <assert.h>
#include "templatefactory.h"

TemplateFactory * TemplateFactory::singletonInstance = NULL;

TemplateFactory::TemplateFactory()
{
	assert(!singletonInstance);
	singletonInstance = this;
}

TemplateFactory::~TemplateFactory()
{
	assert(singletonInstance);
	singletonInstance = NULL;
}

TemplateFactory * TemplateFactory::getInstance()
{
	return singletonInstance;
}

QString TemplateFactory::absolutePath() const
{
	return templatesPath;
}

QList<Template> TemplateFactory::templates()
{
	return filteredTemplates(projectTypeFilter, multiplicityFilter);
}

QList<Template> TemplateFactory::filteredTemplates(const QString projectType, const Template::TemplateMultiplicity multiplicity)
{
	QList<Template> templatesFilteredList;

	foreach(Template templateObj, templatesList)
	{
		bool matched = templateObj.multiplicity() >= multiplicity;

		if (!projectType.isEmpty())
			matched = matched && templateObj.supportedProjects().contains(projectType);

		if (matched)
			templatesFilteredList.append(templateObj);
	}

	return templatesFilteredList;
}

void TemplateFactory::setFilter(const QString projectType, const Template::TemplateMultiplicity multiplicity)
{
	projectTypeFilter = projectType;
	multiplicityFilter = multiplicity;
}

void TemplateFactory::load(const QString path)
{
	templatesList.clear();

	QDir templatesDir(path);

	if (!templatesDir.exists())
		return;

	foreach (QString templateName, templatesDir.entryList(QDir::Dirs|QDir::Readable|QDir::NoDotAndDotDot))
	{
		if (templatesDir.exists(templateName + QDir::separator() + "template-details.xml"))
		{
			Template _template(templatesDir.absoluteFilePath(templateName + QDir::separator() + "template-details.xml"));
			_template.templateID = templateName;
			templatesList.append(_template);
		}
	}

	templatesPath = path;
}

static TemplateFactory templateFactory;

