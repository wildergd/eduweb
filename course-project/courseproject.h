#ifndef COURSEPROJECT_H
#define COURSEPROJECT_H

#include <QStringList>
#include "iplugin.h"
#include "iproject.h"
#include "iprojectcanbecontained.h"
#include "iprojectdescription.h"
#include "ireusable.h"
#include "iconfigurable.h"
#include "course.h"
#include "topic.h"
#include "lecture.h"

class CourseProject: public QObject, public IProject, public IProjectCanBeContained, public IReusable, public IConfigurable
{
	Q_OBJECT
    Q_INTERFACES(IProject IPlugin IProjectCanBeContained IReusable IConfigurable)
public:
	QString pluginName() const;
	QString pluginDisplayName() const;
	QString pluginIcon() const;
	QString pluginVersion() const;
	QString pluginCompatibilityVersion() const;
	QString pluginAuthor() const;
	QString pluginVendor() const;
	QString pluginUrl() const;
	QString pluginDescription() const;
	QString pluginCopyright() const;
	QString pluginLicense() const;
	QStringList pluginDependencies() const;
    QString group() const;
    bool launch(IProjectDescription * projectDescription = 0, SettingsManager* settings = 0);
	bool save();

	QStringList projectsCanBeLinkedTo();
	
	void launchConfig(SettingsManager* settings);

    static void createCourseDefaults(Course* course);
    static void createTopicDefaults(Topic* topic);
    static void createLectureDefaults(Lecture* lecture);

private:	
	static SettingsManager* settings;
	QString dataFileName;
	Course* course;
};

#endif // COURSEPROJECT_H
