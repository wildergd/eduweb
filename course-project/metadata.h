#ifndef METADATA_H
#define METADATA_H

#include <QHash>
#include <QDomElement>

class Metadata
{
public:
    class Field {
    public:
        QString id;
        QString title;
        QString value;
        int order;
        bool isRemovable;
        bool isVisible;
    };

    Metadata();
    ~Metadata();

    Metadata::Field* addField();
    void deleteField(const QString fieldId);
    Metadata::Field* getField(const QString fieldId);
    QHash<int, Metadata::Field*> fields();

    void clearFields();

    void fromXml(QDomElement & rootNode);
    QDomElement & toXml(QDomElement & rootNode);
    QString toJSON();


private:
    QHash<QString, Metadata::Field*> fieldsList;
};

#endif // METADATA_H
