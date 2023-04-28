#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QPixmap>
#include <QStringList>
#include "templateconfigparam.h"

class TemplateFactory;

class Template
{
	friend class TemplateFactory;
	
public:
	typedef enum _TemplateMultiplicity {
		MultipleProjects = 0x1,
		SingleProject = 0
	} TemplateMultiplicity;

	Template(const QString fileName);
	~Template();

	QString mainFile() const;
	QString id() const;
	QString name() const;
	QString author() const;
	QString description() const;
	TemplateMultiplicity multiplicity() const;
	QPixmap screenshot() const;
	QString screenshotPath() const;
	QStringList supportedProjects() const;
	QList<TemplateConfigParam> configParams() const;

private:
	QString templateName;
	QString templateAuthor;
	QString templateDescription;
	TemplateMultiplicity templateMultiplicity;
	QPixmap templateThumbnail;
	QString templateThumbnailFile;
	QStringList templateSupportedProjects;
	QList<TemplateConfigParam> templateConfigParams;
	QString templateMainFile;
	QString templateID;

	void load(const QString fileName);
};

#endif // TEMPLATE_H
