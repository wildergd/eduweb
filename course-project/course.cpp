#include <QStringList>
#include <QUuid>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QTextStream>
#include <QTextCodec>
#include <QCryptographicHash>
#include "course.h"

Course::Course(const QString folder)
{
    courseName = QString::fromUtf8("Course Title");
    courseFolder.setPath(folder);
    createFolderStructure();

#ifdef COURSE_PROJECT
    if (Course::initFunc)
        Course::initFunc(this);
#endif
}

Course::Course(const QString folder, QString dataFileName)
{
    courseName = QString::fromUtf8("Course Title");
    courseFolder.setPath(folder);
    createFolderStructure();
    loadFromFile(dataFileName);
}

Course::~Course()
{
    foreach(Topic* topic, topicsList)
    {
        topicsList.remove(topic->id());
        delete topic;
    }

    foreach(Resource::Category* category, courseResourcesCategories)
    {
        courseResourcesCategories.remove(category->id);
        delete category;
    }
}

void Course::createFolderStructure()
{
    if (!courseFolder.exists("resources"))
        courseFolder.mkdir("resources");
}


QString Course::name() const
{
    return courseName;
}

QString Course::resourcesDir() const
{
    return courseFolder.absoluteFilePath("resources");
}

Metadata& Course::programme()
{
    return courseProgramme;
}

QHash<int, Topic*> Course::topics()
{
    QHash<int, Topic*> sortedTopicsList;
    foreach(Topic* topic, topicsList)
        sortedTopicsList.insert(topic->order(), topic);

    return sortedTopicsList;
}

QHash<int, Lecture*> Course::lectures()
{
    QHash<int, Lecture*> sortedLecturesList;
    foreach(Lecture* lecture, lecturesList)
        sortedLecturesList.insert(lecture->order(), lecture);

    return sortedLecturesList;
}

QHash<QString, Resource*> Course::resources()
{
    return resourcesList;
}

QHash<int,Resource::Category*> Course::resourcesCategories()
{
    QHash<int,Resource::Category*> resourcesCategoriesList;
    foreach(Resource::Category* category, courseResourcesCategories)
        resourcesCategoriesList.insert(category->order, category);

    return resourcesCategoriesList;
}

Topic* Course::getTopic(const QString topicId)
{
    if (!topicsList.contains(topicId))
        return NULL;

    return topicsList.value(topicId);
}

Topic* Course::addTopic()
{
    Topic* topic = new Topic();
    topicsList.insert(topic->id(), topic);

    return topic;
}

void Course::deleteTopic(const QString topicId)
{
    Topic* topic = getTopic(topicId);
    if (!topic)
        return;

    topicsList.remove(topic->id());
    delete topic;
}

Lecture* Course::getLecture(const QString lectureId)
{
    if (!lecturesList.contains(lectureId))
        return NULL;

    return lecturesList.value(lectureId);
}

Lecture* Course::addLecture()
{
    Lecture* lecture = new Lecture();
    lecturesList.insert(lecture->id(), lecture);

    return lecture;
}

void Course::deleteLecture(const QString lectureId)
{
    Lecture* lecture = getLecture(lectureId);
    if (!lecture)
        return;

    lecturesList.remove(lecture->id());
    delete lecture;
}

Resource* Course::getResource(const QString resourceId)
{
    if (!resourcesList.contains(resourceId))
        return NULL;

    return resourcesList.value(resourceId);
}

Resource* Course::addResource()
{
    Resource* resource = new Resource();
    resourcesList.insert(resource->id(), resource);

    return resource;
}

void Course::addResourceFromFile(const QString fileName)
{
    Resource* resource = addResource();
    resource->addFile(fileName);
}

void Course::deleteResource(const QString resourceId)
{
    Resource* resource= getResource(resourceId);
    if (!resource)
        return;

    foreach(QString file, resource->files())
        QFile::remove(courseFolder.absoluteFilePath("resources/" + file));

    resourcesList.remove(resourceId);
    delete resource;
}

Resource::Category* Course::getResourceCategory(const QString categoryId)
{
    if (!courseResourcesCategories.contains(categoryId))
        return NULL;

    return courseResourcesCategories.value(categoryId);
}

Resource::Category* Course::addResourceCategory()
{
    Resource::Category* category = new Resource::Category;
    category->id = QUuid::createUuid();
    category->name = QObject::trUtf8("New Resource Category");
    category->order = courseResourcesCategories.count();
    courseResourcesCategories.insert(category->id, category);

    return category;
}

void Course::deleteResourceCategory(const QString categoryId)
{
    Resource::Category* category = getResourceCategory(categoryId);
    if (!category)
        return;

    courseResourcesCategories.remove(categoryId);
    delete category;
}

void Course::setName(QString value)
{
    if (courseName.compare(value) != 0)
        courseName = value;
}

bool Course::loadFromFile(const QString fileName)
{
    QFile xmlFile(fileName);
    if (!xmlFile.open(QFile::ReadOnly | QFile::Text))
        return false;

    QDomDocument xmlDoc;
    if (!xmlDoc.setContent(&xmlFile))
    {
        xmlFile.close();
        return false;
    }

    xmlFile.close();

    QDomElement rootNode = xmlDoc.documentElement();
    fromXml(rootNode);

    return true;
}

bool Course::saveToFile(const QString fileName)
{
    QDomDocument xmlDoc;

    QFile xmlFile(fileName);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text))
        return false;

    QDomElement rootNode = xmlDoc.createElement("course");
    xmlDoc.appendChild(rootNode);

    toXml(rootNode);

    QTextStream stream(&xmlFile);
    stream.setCodec(QTextCodec::codecForName("UTF-8"));
    xmlDoc.save(stream, 4, QDomNode::EncodingFromTextStream);

    xmlFile.close();

    return true;
}

void Course::fromXml(QDomElement & rootNode)
{
    bool ok;
    if (rootNode.childNodes().isEmpty())
        return;

    QDomElement titleNode = rootNode.firstChildElement("title");
    if (!titleNode.isNull())
        courseName = titleNode.firstChild().nodeValue();

    // loading programme
    QDomElement programmeNode = rootNode.firstChildElement("programme");
    if (!programmeNode.isNull())
        courseProgramme.fromXml(programmeNode);

    // loading topics
    QDomElement topicsNode = rootNode.firstChildElement("topics");
    /*	if (!topicsNode.isNull())
        courseTopics.fromXml(topicsNode);*/

    // loading lectures
    QDomElement lecturesNode = rootNode.firstChildElement("lectures");
    /*	if (!lecturesNode.isNull())
        courseLectures.fromXml(lecturesNode);*/

    // loading resources
    QDomElement courseResourcesNode = rootNode.firstChildElement("resources");
    if (!courseResourcesNode.isNull()) {
        // loading resources categories
        QDomElement courseResourcesCategoriesNode = courseResourcesNode.firstChildElement("categories");
        if (!courseResourcesCategoriesNode.isNull()) {
            QDomNodeList categories = courseResourcesCategoriesNode.elementsByTagName("category");
            if (!categories.isEmpty())
            {
                // remove existing categories
                foreach(Resource::Category* category, courseResourcesCategories)
                {
                    courseResourcesCategories.remove(category->id);
                    delete category;
                }

                for(int index = 0; index < categories.count(); index++)
                {
                    QDomElement categoryNode = categories.at(index).toElement();

                    Resource::Category* category = new Resource::Category;
                    category->id = categoryNode.attribute("id", QUuid::createUuid());
                    category->name = categoryNode.attribute("name", "Category");
                    category->order = categoryNode.attribute("order", QString::number(courseResourcesCategories.count())).toUInt(&ok, 10);
                    courseResourcesCategories.insert(category->id, category);
                }
            }
        }

        // loading resources
        QDomNodeList resources = courseResourcesNode.elementsByTagName("resource");
        if (!resources.isEmpty())
        {
            for(int index = 0; index < resources.count(); index++)
            {
                QDomElement resourceNode = resources.at(index).toElement();
                QString id = resourceNode.attribute("id", QUuid::createUuid());
                QString href = resourceNode.attribute("href", "");

                Resource * resource = new Resource(id);

                QDomElement titleNode = resourceNode.firstChildElement(QString::fromUtf8("name"));
                resource->setName(titleNode.firstChild().nodeValue());

                QDomElement categoryNode = resourceNode.firstChildElement(QString::fromUtf8("category"));
                resource->setCategory(categoryNode.firstChild().nodeValue());

                QDomElement authorNode = resourceNode.firstChildElement(QString::fromUtf8("author"));
                resource->setAuthor(authorNode.firstChild().nodeValue());

                QDomElement descriptionNode = resourceNode.firstChildElement(QString::fromUtf8("description"));
                resource->setDescription(descriptionNode.firstChild().nodeValue());

                QDomNodeList files = resourceNode.elementsByTagName("file");
                if (!files.isEmpty())
                {
                    for(int index = 0; index < files.count(); index++)
                    {
                        QDomElement fileNode = files.at(index).toElement();
                        QString fileHref = fileNode.attribute("href", "");

                        if (!fileHref.isEmpty() && QFile::exists(courseFolder.absoluteFilePath("resources/" + fileHref)))
                        {
                            if ((fileHref == href) && !fileHref.contains("resource_"))
                            {
                                QFileInfo info(fileHref);
                                QCryptographicHash hash(QCryptographicHash::Md5);
                                hash.addData(info.fileName().toAscii());
                                QString resourceFileName = "resource_" + hash.result().toHex() + "." + info.completeSuffix();

                                if (QFile::rename(courseFolder.absoluteFilePath("resources/" + fileHref), courseFolder.absoluteFilePath("resources/" + resourceFileName)))
                                {
                                    href = resourceFileName;
                                    fileHref = resourceFileName;
                                }
                            }

                            bool isMainFile = fileHref == href;
                            resource->addFile(fileHref, isMainFile);
                        }
                    }

                }

                if (!resource->id().isEmpty())
                    resourcesList.insert(resource->id(), resource);
            }
        }
    }
}

QDomElement & Course::toXml(QDomElement & rootNode)
{
    QDomDocument xmlDoc;

    QDomElement nodeTitle = xmlDoc.createElement("title");
    rootNode.appendChild(nodeTitle);

    QDomText nodeText = xmlDoc.createTextNode(courseName);
    nodeTitle.appendChild(nodeText);

    // programme
    QDomElement nodeProgramme = xmlDoc.createElement("programme");
    rootNode.appendChild(nodeProgramme);
    courseProgramme.toXml(nodeProgramme);

    // topics
    QDomElement nodeTopics = xmlDoc.createElement("topics");
    rootNode.appendChild(nodeTopics);
    if (!topics().isEmpty())
    {
        foreach(Topic* topic, topics())
        {
            QDomElement topicNode = xmlDoc.createElement("topic");
            nodeTopics.appendChild(topicNode);

            topic->toXml(topicNode);
        }
    }

    // lectures
    QDomElement nodeLectures = xmlDoc.createElement("lectures");
    rootNode.appendChild(nodeLectures);
    if (!lectures().isEmpty())
    {
        foreach(Lecture* lecture, lectures())
        {
            QDomElement lectureNode = xmlDoc.createElement("lecture");
            nodeLectures.appendChild(lectureNode);

            lecture->toXml(lectureNode);
        }

    }

    // resources 
    if (!resources().isEmpty() || !resourcesCategories().isEmpty())
    {
		QDomElement nodeResources = xmlDoc.createElement("resources");
		rootNode.appendChild(nodeResources);

		// resources categories
		QDomElement resourcesCategoriesNode = xmlDoc.createElement("categories");
		nodeResources.appendChild(resourcesCategoriesNode);

		foreach(Resource::Category* category, courseResourcesCategories)
		{
			QDomElement resourceCategoryNode = xmlDoc.createElement("category");
			resourcesCategoriesNode.appendChild(resourceCategoryNode);

			resourceCategoryNode.setAttribute("id", category->id);
            resourceCategoryNode.setAttribute("name",  category->name);
            resourceCategoryNode.setAttribute("order",  category->order);
        }

		// resources list
        foreach(Resource* resource, resourcesList)
        {
            QDomElement resourceNode = xmlDoc.createElement("resource");
            nodeResources.appendChild(resourceNode);

            resource->toXml(resourceNode);
        }
    }

    return rootNode;
}

QString Course::toJSON()
{
    QStringList courseJSON;
    courseJSON << "{";

    courseJSON << "\"type\": \"Course\",";
    courseJSON << "\"title\": \"" + courseName.replace('"', "\\\"") + "\",";

    if (!programme().fields().isEmpty())
        courseJSON << "\"programme\": " + courseProgramme.toJSON() + ",";

    if (!topics().isEmpty())
    {
        QStringList topicsJSON;

        foreach(Topic* topic, topics())
            topicsJSON << "\"" + topic->id() + "\": {" + topic->toJSON() + "}";

        courseJSON << "\"topics\": {" + topicsJSON.join(", ") + "},";
    }

    if (!lectures().isEmpty())
    {
        QStringList lecturesJSON;

        foreach(Lecture* lecture, lectures())
            lecturesJSON << "\"" + lecture->id() + "\": {" + lecture->toJSON() + "}";

        courseJSON << "\"lectures\": {" + lecturesJSON.join(", ") + "},";
    }

    if (!resources().isEmpty() || !resourcesCategories().isEmpty())
    {
        QStringList courseResourcesJSON;

        if (!resourcesCategories().isEmpty())
        {
            QStringList categoriesJSON;
            foreach(Resource::Category* category, courseResourcesCategories)
                categoriesJSON << "\"" + category->id + "\": {\"name\": \"" + category->name.replace('"', "\\\"") + "\"}";

            courseResourcesJSON << "\"categories\": {" + categoriesJSON.join(", ") + "}";
        }

        if (!resources().isEmpty())
        {
            QStringList resourcesJSON;

            foreach(Resource* resource, resources())
                resourcesJSON << "\"" + resource->id() + "\": {" + resource->toJSON() + "}";

            courseResourcesJSON << "\"resourcesList\": {" + resourcesJSON.join(", ") + "}";
        }

        courseJSON << "\"resources\": {" + courseResourcesJSON.join(", ") + "}";
    }

    courseJSON << "}";

    return courseJSON.join("");
}

