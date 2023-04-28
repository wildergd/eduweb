/**
  * eduWeb main application
  *
  * @author: Wilder González Díaz
  * @version: 1.0
  *
  */

#include <QtDebug>
#include <QApplication>
#include <QSplashScreen>
#include <QDir>
#include <QTranslator>
#include <QLocale>
#include <QResource>
#include <QFile>
#include <QStyleFactory>
#include <QDateTime>
#include "mainwindow.h"
#include "pluginmanager.h"
#include "settingsmanager.h"
#include "workspace.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(resources);
    app.setApplicationName("eduWeb");

    QString appPath(QApplication::applicationDirPath());
    QDir appDir(QApplication::applicationDirPath());

    /* loading splash screen */
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/splash/splash.png"));
    splash->show();

//    app.processEvents();

    /* loading settings */
    SettingsManager::instance()->initSettings();

    if (!SettingsManager::instance()->contains("style"))
        SettingsManager::instance()->setValue("style", QVariant::fromValue(QString("Cleanlooks")));

    if (!SettingsManager::instance()->contains("language"))
    {
        QString language = QLocale::system().name();
        language.resize(2);
        SettingsManager::instance()->setValue("language", QVariant::fromValue(language));
    }

    if (!SettingsManager::instance()->contains("pluginsDir"))
        SettingsManager::instance()->setValue("pluginsDir", QVariant::fromValue(QString("plugins")), QSettings::SystemScope);

    if (!SettingsManager::instance()->contains("languagesDir"))
        SettingsManager::instance()->setValue("languagesDir", QVariant::fromValue(QString("translations")), QSettings::SystemScope);

    if (!SettingsManager::instance()->contains("workspaceDir"))
    {
        if (!QDir::home().exists("." + app.applicationName() + "/projects"))
            QDir::home().mkpath(QDir::home().absoluteFilePath("." + app.applicationName() + "/projects"));
        SettingsManager::instance()->setValue("workspaceDir", QVariant::fromValue(QDir::home().absoluteFilePath("." + app.applicationName() + "/projects")));
    }

    /* setting style */
    QApplication::setStyle(QStyleFactory::create(SettingsManager::instance()->value("style").toString()));

    /* loading plugins */
    splash->showMessage(QObject::trUtf8("Loading plugins..."), Qt::AlignBottom |Qt::AlignRight, QColor::fromRgb(255, 255, 255));
    PluginManager::instance()->load(SettingsManager::instance()->value("pluginsDir").toString());

    /* loading workspace */
    splash->showMessage(QObject::trUtf8("Loading workspace..."), Qt::AlignBottom |Qt::AlignRight, QColor::fromRgb(255, 255, 255));
    Workspace::getInstance()->load(SettingsManager::instance()->value("workspaceDir").toString());

    /* creating and showing the main form */
    MainWindow mainForm;
    mainForm.show();

    /* deleting splash screen */
    splash->finish(&mainForm);
    delete splash;

    /* starting application thread */
    int exitCode = app.exec();

    /* finalizing application and returning the exit code */
    return exitCode;
}
