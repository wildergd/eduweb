#ifndef ACTIONPROGRESS_H
#define ACTIONPROGRESS_H

#include <QDesignerCustomWidgetInterface>

class ActionProgress: public QObject, public QDesignerCustomWidgetInterface
{
	Q_OBJECT
	Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
	ActionProgress(QObject *parent = 0);

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

#endif // ACTIONPROGRESS_H
