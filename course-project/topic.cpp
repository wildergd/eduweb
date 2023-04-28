#include <QUuid>
#include <QStringList>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QTextStream>
#include <QTextCodec>
#include "topic.h"

Topic::Topic()
{
    topicId = QUuid::createUuid();
    topicName = QString::fromUtf8("Type topic title");
    topicIsVisible = true;

#ifdef COURSE_PROJECT
    if (Topic::initFunc)
        Topic::initFunc(this);
#endif
}

Topic::Topic(const QString id)
{
    topicId = id;
    topicName = QString::fromUtf8("Type topic title");
    topicIsVisible = true;

#ifdef COURSE_PROJECT
    if (Topic::initFunc)
        Topic::initFunc(this);
#endif
}

Topic::Topic(QDomElement & rootNode)
{
    topicName = QString::fromUtf8("Type topic title");
    topicIsVisible = true;
    fromXml(rootNode);
}

Topic::~Topic()
{

}

QString Topic::id() const
{
    return topicId;
}

QString Topic::name() const
{
    return topicName;
}

int Topic::order() const
{
    return topicOrder;
}

bool Topic::isVisible() const
{
    return topicIsVisible;
}

Metadata& Topic::design()
{
    return topicDesign;
}

QList<QString>& Topic::lectures()
{
    return topicLectures;
}

QList<QString>& Topic::resources()
{
    return topicResources;
}

void Topic::setName(QString value)
{
    if (topicName.compare(value) != 0)
        topicName = value;
}

void Topic::setOrder(const int value)
{
    topicOrder = value;
}

void Topic::setVisible(const bool value)
{
    topicIsVisible = value;
}

void Topic::fromXml(QDomElement & rootNode)
{

}

QDomElement& Topic::toXml(QDomElement & rootNode)
{

}

QString Topic::toJSON()
{
    QStringList json;

    json << "\"" + topicId + "\": {";
    json << "\"title\": \"" + topicName.replace('"', "\\\"") + "\"," ;
    json << "\"design\": " + topicDesign.toJSON();

    if (!lectures().isEmpty())
    {
        json << "," << "\"lectures\": [\"" + QStringList(topicLectures).join("\",\"") + "\"]" ;
    }

    if (!resources().isEmpty())
    {
        json << "," << "\"resources\": [\"" + QStringList(topicResources).join("\",\"") + "\"]" ;
    }

    json << "}";

    return json.join("");
}
