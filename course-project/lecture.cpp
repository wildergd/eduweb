#include <QUuid>
#include <QStringList>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QTextStream>
#include <QTextCodec>
#include "lecture.h"

Lecture::Lecture()
{
    lectureId = QUuid::createUuid();
    lectureName = QString::fromUtf8("Type lecture title");
    lectureIsVisible = true;

#ifdef COURSE_PROJECT
    if (Lecture::initFunc)
        Lecture::initFunc(this);
#endif
}

Lecture::Lecture(const QString id)
{
    lectureId = id;
    lectureName = QString::fromUtf8("Título de la clase");
    lectureIsVisible = true;

#ifdef COURSE_PROJECT
    if (Lecture::initFunc)
        Lecture::initFunc(this);
#endif
}

Lecture::Lecture(QDomElement & rootNode)
{
    lectureName = QString::fromUtf8("Título de la clase");
    lectureIsVisible = true;
    fromXml(rootNode);
}

Lecture::~Lecture()
{
}

QString Lecture::id() const
{
    return lectureId;
}

QString Lecture::name() const
{
    return lectureName;
}

QString Lecture::topic() const
{
    return topicId;
}

int Lecture::order() const
{
    return lectureOrder;
}

bool Lecture::isVisible() const
{
    return lectureIsVisible;
}

Metadata& Lecture::design()
{
    return lectureDesign;
}

QList<QString>& Lecture::resources()
{
    return lectureResources;
}

void Lecture::setName(const QString value)
{
    if (lectureName.compare(value) != 0)
        lectureName = value;
}

void Lecture::setTopic(const QString value)
{
    topicId = value;
}

void Lecture::setOrder(const int value)
{
    lectureOrder = value;
}

void Lecture::setVisible(const bool value)
{
    lectureIsVisible = value;
}

void Lecture::fromXml(QDomElement & rootNode)
{

}

QDomElement & Lecture::toXml(QDomElement & rootNode)
{

}

QString Lecture::toJSON()
{

}

