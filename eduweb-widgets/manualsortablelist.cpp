#include <QtPlugin>
#include "manualsortablelist.h"
#include "manualsortablelistwidget.h"

ManualSortableList::ManualSortableList(QObject *parent): QObject(parent)
{
     initialized = false;
}

QString ManualSortableList::name() const
{
	return "ManualSortableListWidget";
}

QString ManualSortableList::group() const
{
	return "Item Widgets (Item-Based)";
}

QString ManualSortableList::toolTip() const
{
	return "";
}

QString ManualSortableList::whatsThis() const
{
	return "";
}

QString ManualSortableList::includeFile() const
{
	return "manualsortablelistwidget.h";
}

QIcon ManualSortableList::icon() const
{
	return QIcon();
}

bool ManualSortableList::isContainer() const
{
	return false;
}

QWidget * ManualSortableList::createWidget(QWidget *parent)
{
	return new ManualSortableListWidget(parent);
}

bool ManualSortableList::isInitialized() const
{
	return initialized;
}

void ManualSortableList::initialize(QDesignerFormEditorInterface *editor)
{
	if (initialized)
		return;

	initialized = true;
}

QString ManualSortableList::domXml() const
{
	return	"<ui language=\"c++\">\n"
		" <widget class=\"ManualSortableListWidget\" name=\"manualSortableListWidget\">\n"
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

Q_EXPORT_PLUGIN2(manualSortableList, ManualSortableList);
