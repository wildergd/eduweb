#ifndef TEMPLATEFACTORY_H
#define TEMPLATEFACTORY_H

#include <QList>
#include "template.h"

class TemplateFactory
{
public:
	TemplateFactory();
	~TemplateFactory();

	static TemplateFactory * getInstance();
	QString absolutePath() const;
	QList<Template> templates();
	void load(const QString path);
	void setFilter(const QString projectType, const Template::TemplateMultiplicity multiplicity);
private:
	QList<Template> templatesList;
	static TemplateFactory* singletonInstance;
	QString projectTypeFilter;
	Template::TemplateMultiplicity multiplicityFilter;
	QString templatesPath;

	QList<Template> filteredTemplates(const QString projectType, const Template::TemplateMultiplicity multiplicity = Template::SingleProject);
};

#endif // TEMPLATEFACTORY_H
