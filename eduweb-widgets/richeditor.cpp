#include <QtPlugin>
#include "richeditor.h"
#include "richeditorwidget.h"

RichEditor::RichEditor(QObject *parent): QObject(parent)
{
     initialized = false;
}

QString RichEditor::name() const
{
	return "RichEditorWidget";
}

QString RichEditor::group() const
{
	return "Input Widgets";
}

QString RichEditor::toolTip() const
{
	return "";
}

QString RichEditor::whatsThis() const
{
	return "";
}

QString RichEditor::includeFile() const
{
	return "richeditorwidget.h";
}

QIcon RichEditor::icon() const
{
	return QIcon();
}

bool RichEditor::isContainer() const
{
	return false;
}

QWidget * RichEditor::createWidget(QWidget *parent)
{
	return new RichEditorWidget(parent);
}

bool RichEditor::isInitialized() const
{
	return initialized;
}

void RichEditor::initialize(QDesignerFormEditorInterface *editor)
{
	if (initialized)
		return;

	initialized = true;
}

QString RichEditor::domXml() const
{
	return	"<ui language=\"c++\">\n"
		" <widget class=\"RichEditorWidget\" name=\"richEditorWidget\">\n"
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

Q_EXPORT_PLUGIN2(richEditor, RichEditor);
