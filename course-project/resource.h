#ifndef RESOURCE_H
#define RESOURCE_H

#include <QDomElement>
#include <QList>

class Resource
{
public:
    class Category {
    public:
        QString id;
        QString name;
        int order;
    };

    Resource();
    Resource(const QString id);
    ~Resource();

    QString id() const;
    QString name() const;
    QString author() const;
    QString category() const;
    QString description() const;
    QString href() const;
    QList<QString> files();

    void setName(const QString value);
    void setAuthor(const QString value);
    void setCategory(const QString value);
    void setDescription(const QString value);

    bool addFile(const QString fileName, const bool isMainFile = true);
    QDomElement & toXml(QDomElement & rootNode);
    QString toJSON();

private:
    QString resourceId;
    QString resourceName;
    QString resourceAuthor;
    QString resourceDescription;
    QString resourceHref;
    QString resourceCategory;
    QList<QString> linkedFiles;
};

#endif // RESOURCE_H
