#include <QtPlugin>
#include "actionprogress.h"
#include "actionprogresswidget.h"

ActionProgress::ActionProgress(QObject *parent): QObject(parent)
{
     initialized = false;
}

QString ActionProgress::name() const
{
	return "ActionProgressWidget";
}

QString ActionProgress::group() const
{
	return "Display Widgets";
}

QString ActionProgress::toolTip() const
{
	return "";
}

QString ActionProgress::whatsThis() const
{
	return "";
}

QString ActionProgress::includeFile() const
{
	return "actionprogresswidget.h";
}

QIcon ActionProgress::icon() const
{
	return QIcon();
}

bool ActionProgress::isContainer() const
{
	return false;
}

QWidget * ActionProgress::createWidget(QWidget *parent)
{
	return new ActionProgressWidget(parent);
}

bool ActionProgress::isInitialized() const
{
	return initialized;
}

void ActionProgress::initialize(QDesignerFormEditorInterface *editor)
{
	if (initialized)
		return;

	initialized = true;
}

QString ActionProgress::domXml() const
{
	return	"<ui language=\"c++\">\n"
		" <widget class=\"ActionProgressWidget\" name=\"actionProgressWidget\">\n"
		"  <property name=\"geometry\">\n"
		"   <rect>\n"
		"    <x>0</x>\n"
		"    <y>0</y>\n"
		"    <width>410</width>\n"
		"    <height>65</height>\n"
		"   </rect>\n"
		"  </property>\n"
		" </widget>\n"
		"</ui>";
}

Q_EXPORT_PLUGIN2(actionProgress, ActionProgress);
