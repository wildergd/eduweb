#include <QUuid>
#include <QStringList>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QTextStream>
#include <QTextCodec>
#include "resource.h"

Resource::Resource()
{
    resourceId = QUuid::createUuid();
}

Resource::Resource(const QString id)
{
    resourceId = id;
}

Resource::~Resource()
{

}

QString Resource::id() const
{
        return resourceId;
}

QString Resource::name() const
{
        return resourceName;
}

QString Resource::author() const
{
        return resourceAuthor;
}

QString Resource::category() const
{
        return resourceCategory;
}

QString Resource::description() const
{
        return resourceDescription;
}

QString Resource::href() const
{
        return resourceHref;
}

QList<QString> Resource::files()
{
        return linkedFiles;
}

void Resource::setName(const QString value)
{
    if (resourceName.compare(value) != 0)
        resourceName = value;
}

void Resource::setAuthor(const QString value)
{
    if (resourceAuthor.compare(value) != 0)
        resourceAuthor = value;
}

void Resource::setCategory(const QString value)
{
    if (resourceCategory.compare(value) != 0)
        resourceCategory = value;
}

void Resource::setDescription(const QString value)
{
    if (resourceDescription.compare(value) != 0)
        resourceDescription = value;
}

bool Resource::addFile(const QString fileName, const bool isMainFile)
{
    if (linkedFiles.contains(fileName))
        return false;

   linkedFiles.append(fileName);

    if (isMainFile)
            resourceHref = fileName;

    return true;
}

QDomElement& Resource::toXml(QDomElement & rootNode)
{

}

QString Resource::toJSON()
{

}
