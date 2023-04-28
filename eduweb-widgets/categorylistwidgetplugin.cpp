#include <QtPlugin>
#include "categorylistwidgetplugin.h"
#include "categorylistwidget.h"

CategoryListWidgetPlugin::CategoryListWidgetPlugin(QObject *parent): QObject(parent)
{
     initialized = false;
}

QString CategoryListWidgetPlugin::name() const
{
	return "CategoryListWidget";
}

QString CategoryListWidgetPlugin::group() const
{
	return "Item Widgets (Item-Based)";
}

QString CategoryListWidgetPlugin::toolTip() const
{
	return "";
}

QString CategoryListWidgetPlugin::whatsThis() const
{
	return "";
}

QString CategoryListWidgetPlugin::includeFile() const
{
	return "categorylistwidget.h";
}

QIcon CategoryListWidgetPlugin::icon() const
{
	return QIcon();
}

bool CategoryListWidgetPlugin::isContainer() const
{
	return false;
}

QWidget * CategoryListWidgetPlugin::createWidget(QWidget *parent)
{
	return new CategoryListWidget(parent);
}

bool CategoryListWidgetPlugin::isInitialized() const
{
	return initialized;
}

void CategoryListWidgetPlugin::initialize(QDesignerFormEditorInterface *editor)
{
	if (initialized)
		return;

	initialized = true;
}

QString CategoryListWidgetPlugin::domXml() const
{
	return	"<ui language=\"c++\">\n"
		" <widget class=\"CategoryListWidget\" name=\"CategoryListWidget\">\n"
		"  <property name=\"geometry\">\n"
		"   <rect>\n"
		"    <x>0</x>\n"
		"    <y>0</y>\n"
		"    <width>400</width>\n"
		"    <height>270</height>\n"
		"   </rect>\n"
		"  </property>\n"
		" </widget>\n"
		"</ui>";
}

Q_EXPORT_PLUGIN2(categoryListWidgetPlugin, CategoryListWidgetPlugin);
