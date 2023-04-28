#include <QtGui>
#include "courseproject.h"
#include "courseprojectconfigdialog.h"
#include "courseprojecteditdialog.h"
#include "settingsmanager.h"

SettingsManager* CourseProject::settings = NULL;

void (*Course::initFunc)(Course*) = CourseProject::createCourseDefaults;
void (*Topic::initFunc)(Topic*) = CourseProject::createTopicDefaults;
void (*Lecture::initFunc)(Lecture*) = CourseProject::createLectureDefaults;

QString CourseProject::pluginName() const
{
	return "CourseProject";
}

QString CourseProject::pluginDisplayName() const
{
	return trUtf8("Course");
}

QString CourseProject::group() const 
{
	return trUtf8("Postgraduate Education");
}

QString CourseProject::pluginIcon() const
{
	return ":/course-project-icon.png";
}

QString CourseProject::pluginVersion() const
{
	return "1.3";
}

QString CourseProject::pluginCompatibilityVersion() const
{
	return "1.2";
}

QString CourseProject::pluginAuthor() const
{
	return QString::fromUtf8("Msc. Wilder González Díaz (wilder@uclv.edu.cu)\nMsc. Isaac Iran Cabrera Ruiz (isaacicr@uclv.edu.cu)");
}

QString CourseProject::pluginVendor() const
{
	return trUtf8("Central University \"Marta Abreu\" of Las Villas");;
}

QString CourseProject::pluginUrl() const
{
	return "";
}

QString CourseProject::pluginDescription() const
{
	return "";
}

QString CourseProject::pluginCopyright() const
{
	return "&copy; 2011 " + trUtf8("Central University \"Marta Abreu\" of Las Villas");
}

QString CourseProject::pluginLicense() const
{
	return "";
}

QStringList CourseProject::pluginDependencies() const
{
	return QStringList();
}

QStringList CourseProject::projectsCanBeLinkedTo()
{
	QStringList referencingProjects;
	referencingProjects << "DiplomaProgramProject";
	referencingProjects << "MasterProgramProject";
	return referencingProjects;
}

void CourseProject::launchConfig(SettingsManager* settings)
{
    CourseProjectConfigDialog dlgConfig;
    dlgConfig.init(settings);
    dlgConfig.exec();
    if (dlgConfig.result() == QDialog::Accepted)
    {
        settings->beginGroup("CourseProject");

        QString metadata = QString::fromAscii(dlgConfig.programmeMetadata().join(", ").toUtf8().toBase64().data());
        settings->setValue("courseProgrammeDefaultFields", QVariant::fromValue(metadata));

        metadata = QString::fromAscii(dlgConfig.topicMetadata().join(", ").toUtf8().toBase64().data());
        settings->setValue("courseTopicDesignFields", QVariant::fromValue(metadata));

        metadata = QString::fromAscii(dlgConfig.lectureMetadata().join(", ").toUtf8().toBase64().data());
        settings->setValue("courseLectureDesignFields", QVariant::fromValue(metadata));

        metadata = QString::fromAscii(dlgConfig.resourcesCategories().join(", ").toUtf8().toBase64().data());
        settings->setValue("courseResourcesCategories", QVariant::fromValue(metadata));
        settings->endGroup();

        settings->sync();
    }
}

bool CourseProject::launch(IProjectDescription * projectDescription, SettingsManager* settings)
{
	CourseProject::settings = settings;

    course = new Course(projectDescription->getProjectLocation());
    dataFileName = projectDescription->getProjectLocation().append("/course-data.xml");

    if (!QFile(dataFileName).exists()) {
        course->saveToFile(dataFileName);
    }
    else {
        course->loadFromFile(dataFileName);
    }

    course->setName(projectDescription->getProjectName());

    CourseProjectEditDialog dlgEditCourse(course);
    dlgEditCourse.setWindowFlags(Qt::Window);
    dlgEditCourse.exec();

    course->saveToFile(dataFileName);
    projectDescription->setProjectName(course->name());

    CourseProject::settings = NULL;

	return true;
}

bool CourseProject::save()
{
	course->saveToFile(dataFileName);
	return true;
}

void CourseProject::createCourseDefaults(Course* course)
{
    /* loading course programme fields */
    QString metadata = QString::fromUtf8(QByteArray::fromBase64(CourseProject::settings->value("CourseProject/courseProgrammeDefaultFields").toString().toAscii()).data());
    if (metadata.isEmpty())
    {
        QFile file(":/defaults/default-programme-metadata.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("UTF-8"));

        metadata = in.readAll().split("\n", QString::SkipEmptyParts).join(", ");
    }

    foreach(QString fieldName, metadata.split(", "))
    {
        Metadata::Field* field = course->programme().addField();
        field->title = fieldName;
    }

    /* loading resources categories */
    metadata = QString::fromUtf8(QByteArray::fromBase64(CourseProject::settings->value("CourseProject/courseResourcesCategories").toString().toAscii()).data());
    if (metadata.isEmpty())
    {
        QFile file(":/defaults/default-resources-categories.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("UTF-8"));

        metadata = in.readAll().split("\n", QString::SkipEmptyParts).join(", ");
    }

    foreach(QString categoryName, metadata.split(", "))
    {
        Resource::Category* category = course->addResourceCategory();
        category->name = categoryName;
    }
}

void CourseProject::createTopicDefaults(Topic * topic)
{
	/* loading topic design default fields */
    QString metadata = QString::fromUtf8(QByteArray::fromBase64(CourseProject::settings->value("CourseProject/courseTopicDesignFields").toString().toAscii()).data());
    if (metadata.isEmpty())
    {
        QFile file(":/defaults/default-topic-metadata.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("UTF-8"));

        metadata = in.readAll().split("\n", QString::SkipEmptyParts).join(", ");
    }

    foreach(QString fieldName, metadata.split(", "))
    {
        Metadata::Field* field = topic->design().addField();
        field->title = fieldName;
    }
}

void CourseProject::createLectureDefaults(Lecture* lecture)
{
	/* loading lecture design default fields */
    QString metadata = QString::fromUtf8(QByteArray::fromBase64(CourseProject::settings->value("CourseProject/courseLectureDesignFields").toString().toAscii()).data());
    if (metadata.isEmpty())
    {
        QFile file(":/defaults/default-lecture-metadata.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

        QTextStream in(&file);
        in.setCodec(QTextCodec::codecForName("UTF-8"));

        metadata = in.readAll().split("\n", QString::SkipEmptyParts).join(", ");
    }

    foreach(QString fieldName, metadata.split(", "))
    {
        Metadata::Field* field = lecture->design().addField();
        field->title = fieldName;
    }
}

Q_EXPORT_PLUGIN2(courseProject, CourseProject)
