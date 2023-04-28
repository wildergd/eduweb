#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "eduweb-core.h"
#include <QSettings>

class EDUWEB_CORE_EXPORT SettingsManager
{
public:
	SettingsManager();
	~SettingsManager();

	static SettingsManager * instance();

	QStringList allKeys();
	void beginGroup(const QString & prefix);
	bool contains(const QString & key) const;
	void endGroup();
	QVariant value(const QString & key, const QVariant & defaultValue = QVariant()) const;

	void setValue(const QString & key, const QVariant & value, QSettings::Scope scope = QSettings::UserScope);
	void sync();
	void initSettings();

private:
	static SettingsManager * singletonInstance;
	QSettings * userSettings;
	QSettings * systemSettings;
	QHash<QString, QSettings::Scope> registeredSettings;
};

#endif // SETTINGSMANAGER_H
