#ifndef RICHEDITOR_H
#define RICHEDITOR_H

#include <QDesignerCustomWidgetInterface>

class RichEditor: public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	RichEditor(QObject *parent = 0);

	QString name() const;
	QString group() const;
	QString toolTip() const;
	QString whatsThis() const;
	QString includeFile() const;
	QIcon icon() const;
	bool isContainer() const;
	QWidget *createWidget(QWidget *parent);
	bool isInitialized() const;
	void initialize(QDesignerFormEditorInterface *editor);
	QString domXml() const;

private:
	bool initialized;
};

#endif
