#include <QtPlugin>
#include "fileselect.h"
#include "fileselectwidget.h"

FileSelect::FileSelect(QObject *parent): QObject(parent)
{
     initialized = false;
}

QString FileSelect::name() const
{
	return "FileSelectWidget";
}

QString FileSelect::group() const
{
	return "Input Widgets";
}

QString FileSelect::toolTip() const
{
	return "";
}

QString FileSelect::whatsThis() const
{
	return "";
}

QString FileSelect::includeFile() const
{
	return "fileselectwidget.h";
}

QIcon FileSelect::icon() const
{
	return QIcon();
}

bool FileSelect::isContainer() const
{
	return false;
}

QWidget * FileSelect::createWidget(QWidget *parent)
{
	return new FileSelectWidget(parent);
}

bool FileSelect::isInitialized() const
{
	return initialized;
}

void FileSelect::initialize(QDesignerFormEditorInterface *editor)
{
	Q_UNUSED(editor);
	if (initialized)
		return;

	initialized = true;
}

QString FileSelect::domXml() const
{
	return	"<ui language=\"c++\">\n"
		" <widget class=\"FileSelectWidget\" name=\"fileSelectWidget\">\n"
		"  <property name=\"geometry\">\n"
		"   <rect>\n"
		"    <x>0</x>\n"
		"    <y>0</y>\n"
		"    <width>400</width>\n"
		"    <height>24</height>\n"
		"   </rect>\n"
		"  </property>\n"
		" </widget>\n"
		"</ui>";
}

Q_EXPORT_PLUGIN2(fileSelect, FileSelect);
