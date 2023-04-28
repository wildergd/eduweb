#ifndef LECTURE_H
#define LECTURE_H

#include <QDomElement>
#include "metadata.h"

class Lecture
{
public:
    Lecture();
    Lecture(const QString id);
    Lecture(QDomElement & rootNode);
    ~Lecture();

    QString id() const;
    QString name() const;
    QString topic() const;
    int order() const;
    bool isVisible() const;
    Metadata& design();
    QList<QString> & resources();

    void setName(const QString value);
    void setTopic(const QString value);
    void setOrder(const int value);
    void setVisible(const bool value);

    void fromXml(QDomElement & rootNode);
    QDomElement & toXml(QDomElement & rootNode);
    QString toJSON();

#ifdef COURSE_PROJECT
    static void (*initFunc)(Lecture*);
#endif

private:
    QString lectureId;
    QString lectureName;
    QString topicId;
    bool lectureIsVisible;
    int lectureOrder;
    Metadata lectureDesign;
    QList<QString> lectureResources;
};

#endif // LECTURE_H
