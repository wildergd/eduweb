#include "templateconfigparam.h"

TemplateConfigParam::TemplateConfigParam(QDomElement rootNode)
{
	paramVarName = rootNode.attribute("varname", "param");
	paramType = rootNode.attribute("type", "string");
	paramIsMandatory = (rootNode.attribute("mandatory", "0").compare("1") == 0) ? true : false;

	QDomElement titleNode = rootNode.firstChildElement("title");
	paramName = titleNode.text();

	QDomElement descriptionNode = rootNode.firstChildElement("description");
	paramDescription = descriptionNode.text();

	QDomElement defaultValueNode = rootNode.firstChildElement("defaultValue");
	paramDefaultValue = defaultValueNode.text();
}

TemplateConfigParam::~TemplateConfigParam()
{
}

QString TemplateConfigParam::name() const
{
	return paramName;
}

QString TemplateConfigParam::varName() const
{
	return paramVarName;
}

QString TemplateConfigParam::type() const
{
	return paramType;
}

QString TemplateConfigParam::defaultValue() const
{
	return paramDefaultValue;
}

QString TemplateConfigParam::description() const
{
	return paramDescription;
}

bool TemplateConfigParam::mandatory() const
{
	return paramIsMandatory;
}
