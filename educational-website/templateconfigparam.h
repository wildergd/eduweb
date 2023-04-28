#ifndef TEMPLATECONFIGPARAM_H
#define TEMPLATECONFIGPARAM_H

#include <QDomElement>

class TemplateConfigParam
{
public:
	TemplateConfigParam(QDomElement rootNode);
	~TemplateConfigParam();

	QString name() const;
	QString varName() const;
	QString type() const;
	QString defaultValue() const;
	QString description() const;
	bool mandatory() const;

private:
	QString paramName;
	QString paramVarName;
	QString paramType;
	QString paramDefaultValue;
	QString paramDescription;
	bool paramIsMandatory;
};

#endif // TEMPLATECONFIGPARAM_H
