#include <QApplication>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QTextCodec>
#include <assert.h>
#include "settingsmanager.h"

SettingsManager * SettingsManager::singletonInstance = NULL;

SettingsManager::SettingsManager()
{
	assert(!singletonInstance);
	singletonInstance = this;
}

SettingsManager::~SettingsManager()
{
	assert(singletonInstance);
	singletonInstance = NULL;

	assert(systemSettings && userSettings);
	systemSettings = NULL;
	userSettings = NULL;
}

SettingsManager * SettingsManager::instance()
{
	return singletonInstance;
}

QStringList SettingsManager::allKeys()
{
	return registeredSettings.keys();
}

void SettingsManager::beginGroup(const QString & prefix)
{
	userSettings->beginGroup(prefix);
}

bool SettingsManager::contains(const QString & key) const
{
	return registeredSettings.keys().contains(key);
}

void SettingsManager::endGroup()
{
	userSettings->endGroup();
}

QVariant SettingsManager::value(const QString & key, const QVariant & defaultValue) const
{
	if (!registeredSettings.keys().contains(key))
		return defaultValue;

	if (registeredSettings.value(key) == QSettings::UserScope)
		return userSettings->value(key, defaultValue);

	return systemSettings->value(key, defaultValue);
}

void SettingsManager::setValue(const QString & key, const QVariant & value, QSettings::Scope scope)
{
	QFileInfo fileInfo(systemSettings->fileName());
	QFileInfo dirInfo(fileInfo.absolutePath());
	if (scope == QSettings::UserScope)
		userSettings->setValue(key, value);
	else if (fileInfo.isWritable() || dirInfo.isWritable())
		systemSettings->setValue(key, value);
	else
		return;

	if (!registeredSettings.keys().contains(key))
		registeredSettings.insert(key, scope);
}

void SettingsManager::sync()
{
	userSettings->sync();
}

void SettingsManager::initSettings()
{
	assert(!userSettings && !systemSettings);
    QDir appDir(QApplication::applicationDirPath());
	userSettings = new QSettings(QDir::home().absoluteFilePath("." + QApplication::applicationName() + "/conf/settings.ini"), QSettings::IniFormat);
    userSettings->setIniCodec(QTextCodec::codecForName("UTF-8"));

    systemSettings = new QSettings(appDir.absoluteFilePath("config.ini"), QSettings::IniFormat);
    systemSettings->setIniCodec(QTextCodec::codecForName("UTF-8"));

    foreach(QString key, userSettings->allKeys())
		registeredSettings.insert(key, QSettings::UserScope);

	foreach(QString key, systemSettings->allKeys())
		registeredSettings.insert(key, QSettings::SystemScope);
}

static SettingsManager settingsManager;
