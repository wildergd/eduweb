#ifndef TOPIC_H
#define TOPIC_H

#include <QDomElement>
#include "metadata.h"

class Topic
{
public:
    Topic();
    Topic(const QString id);
    Topic(QDomElement & rootNode);
    ~Topic();

    QString id() const;
    QString name() const;
    int order() const;
    bool isVisible() const;
    Metadata& design();
    QList<QString> & lectures();
    QList<QString> & resources();

    void setName(QString value);
    void setOrder(const int value);
    void setVisible(const bool value);

    void fromXml(QDomElement & rootNode);
    QDomElement & toXml(QDomElement & rootNode);
    QString toJSON();

#ifdef COURSE_PROJECT
    static void (*initFunc)(Topic*);
#endif

private:
    QString topicId;
    QString topicName;
    bool topicIsVisible;
    int topicOrder;
    Metadata topicDesign;
    QList<QString> topicLectures;
    QList<QString> topicResources;
};

#endif // TOPIC_H
