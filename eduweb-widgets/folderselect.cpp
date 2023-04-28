#include <QtPlugin>
#include "folderselect.h"
#include "folderselectwidget.h"

FolderSelect::FolderSelect(QObject *parent)
	: QObject(parent)
{
     initialized = false;
}

QString FolderSelect::name() const
{
	return "FolderSelectWidget";
}

QString FolderSelect::group() const
{
	return "Input Widgets";
}

QString FolderSelect::toolTip() const
{
	return "";
}

QString FolderSelect::whatsThis() const
{
	return "";
}

QString FolderSelect::includeFile() const
{
	return "folderselectwidget.h";
}

QIcon FolderSelect::icon() const
{
	return QIcon();
}

bool FolderSelect::isContainer() const
{
	return false;
}

QWidget * FolderSelect::createWidget(QWidget *parent)
{
	return new FolderSelectWidget(parent);
}

bool FolderSelect::isInitialized() const
{
	return initialized;
}

void FolderSelect::initialize(QDesignerFormEditorInterface *editor)
{
	Q_UNUSED(editor);
	if (initialized)
		return;

	initialized = true;
}

QString FolderSelect::domXml() const
{
	return	"<ui language=\"c++\">\n"
		" <widget class=\"FolderSelectWidget\" name=\"folderSelectWidget\">\n"
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

Q_EXPORT_PLUGIN2(folderSelect, FolderSelect);
