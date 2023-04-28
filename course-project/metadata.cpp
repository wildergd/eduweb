#include <QDir>
#include <QUuid>
#include <QDomText>
#include <QDomElement>
#include <QDomDocument>
#include "metadata.h"

Metadata::Metadata()
{
}

Metadata::~Metadata()
{
    clearFields();
}

Metadata::Field* Metadata::addField()
{
    Metadata::Field* field = new Metadata::Field();
    field->id = QUuid::createUuid();
    field->isRemovable = true;
    field->isVisible = true;
    field->order = fieldsList.count();

    fieldsList.insert(field->id, field);

    return field;
}

void Metadata::deleteField(const QString fieldId)
{
    Metadata::Field* field = getField(fieldId);
    if (!field)
        return;

    fieldsList.remove(field->id);
    delete field;
}

Metadata::Field* Metadata::getField(const QString fieldId)
{
    if (!fieldsList.contains(fieldId))
        return NULL;

    return fieldsList.value(fieldId);
}

QHash<int, Metadata::Field*> Metadata::fields()
{
    QHash<int, Metadata::Field*> sortedFieldsList;
    foreach(Field* field, fieldsList)
        sortedFieldsList.insert(field->order, field);

    return sortedFieldsList;
}

void Metadata::clearFields()
{
    foreach(Metadata::Field* field, fieldsList)
    {
        fieldsList.remove(field->id);
        delete field;
    }
}

void Metadata::fromXml(QDomElement & rootNode)
{
    QDomNodeList sections = rootNode.elementsByTagName("section");
    if (sections.isEmpty())
        return ;

    clearFields();

    for(int index = 0; index < sections.count(); index++)
    {
        QDomElement section = sections.at(index).toElement();
        QString id = section.attribute("id", "");
        Metadata::Field* field = addField();

        bool ok;

        field->order = section.attribute("order", "10000").toUInt(&ok, 10);;
        field->isRemovable = (section.attribute("removable", "0").toUInt(&ok, 10) == 0) ? false : true;
        field->isVisible = (section.attribute("visible", "1").toUInt(&ok, 10) == 1) ? true : false;

        QDomElement titleNode = section.firstChildElement(QString::fromUtf8("title"));
        field->title = titleNode.firstChild().nodeValue();

        QDomElement valueNode = section.firstChildElement(QString::fromUtf8("value"));
        if (!valueNode.isNull())
            field->value = valueNode.text();
    }
}

QDomElement & Metadata::toXml(QDomElement & rootNode)
{
    QDomDocument xmlDoc;

    foreach(Metadata::Field* field, fieldsList)
    {
        QDomElement fieldNode = xmlDoc.createElement("section");
        rootNode.appendChild(fieldNode);

        fieldNode.setAttribute("visible", field->isVisible);
        fieldNode.setAttribute("removable",  field->isRemovable);
        fieldNode.setAttribute("order", field->order);
        fieldNode.setAttribute("id", field->id);

        QDomElement fieldNodeTitle = xmlDoc.createElement("title");
        fieldNode.appendChild(fieldNodeTitle);

        QDomText fieldNodeText = xmlDoc.createTextNode(field->title);
        fieldNodeTitle.appendChild(fieldNodeText);

        QDomElement fieldNodeValue = xmlDoc.createElement("value");
        fieldNode.appendChild(fieldNodeValue);

        QString valueStr = field->value;
        valueStr.replace(QRegExp("<body([^>]*)>([^<]*)</body>"), "\\2");
        QDomCDATASection fieldNodeValueText = xmlDoc.createCDATASection(valueStr);
        fieldNodeValue.appendChild(fieldNodeValueText);
    }

    return rootNode;
}

QString Metadata::toJSON()
{
    QStringList fieldsJSON;

    for(int index = 0; index < fields().count(); index++)
    {
        Metadata::Field* field = fields().value(index);
        if (field->isVisible)
            fieldsJSON << "{\"name\": \"" + field->title.replace('"', "\\\"") + "\",\"value\": \"" + field->value.replace('"', "\\\"").replace('\n', "\\\n").replace('\r', "") + "\"}";
    }

    return "[" + fieldsJSON.join(",") + "]";
}

