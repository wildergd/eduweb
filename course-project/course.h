#ifndef COURSE_H
#define COURSE_H

#include <QDomElement>
#include <QDir>
#include <QHash>
#include "metadata.h"
#include "topic.h"
#include "lecture.h"
#include "resource.h"

class Course
{
public:
    Course(const QString folder);
    Course(const QString folder, QString dataFileName);
    ~Course();

    QString name() const;
    QString resourcesDir() const;
    Metadata& programme();
    QHash<int, Topic*> topics();
    QHash<int, Lecture*> lectures();
    QHash<QString, Resource*> resources();
    QHash<int,Resource::Category*> resourcesCategories();

    Topic* getTopic(const QString topicId);
    Topic* addTopic();
    void deleteTopic(const QString topicId);

    Lecture* getLecture(const QString lectureId);
    Lecture* addLecture();
    void deleteLecture(const QString lectureId);

    Resource* getResource(const QString resourceId);
    Resource* addResource();
    void addResourceFromFile(const QString fileName);
    void deleteResource(const QString resourceId);

    Resource::Category* getResourceCategory(const QString categoryId);
    Resource::Category* addResourceCategory();
    void deleteResourceCategory(const QString categoryId);

    void setName(QString value);
    bool loadFromFile(const QString fileName);
    bool saveToFile(const QString fileName);

    void fromXml(QDomElement & rootNode);
    QDomElement & toXml(QDomElement & rootNode);
    QString toJSON();

#ifdef COURSE_PROJECT
    static void (*initFunc)(Course*);
#endif

private:
    QDir courseFolder;
    QString courseName;
    Metadata courseProgramme;
    QHash<QString, Topic*> topicsList;
    QHash<QString, Lecture*> lecturesList;
    QHash<QString, Resource*> resourcesList;
    QHash<QString, Resource::Category*> courseResourcesCategories;

    void createFolderStructure();
};

#endif // COURSE_H
