#ifndef ACTIONPROGRESSWIDGET_H
#define ACTIONPROGRESSWIDGET_H

#include <QWidget>
#include <QProgressBar>
#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
#include <QtDesigner/QDesignerExportWidget>
#endif

namespace Ui {
    class ActionProgressWidget;
}

#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
class QDESIGNER_WIDGET_EXPORT ActionProgressWidget : public QWidget
#else
class ActionProgressWidget : public QWidget
#endif
{
    Q_OBJECT

public:
    explicit ActionProgressWidget(QWidget *parent = 0);
    ~ActionProgressWidget();

	QProgressBar * progressBar();
	void setLabel(const QString value);

private:
    Ui::ActionProgressWidget *ui;
};

#endif // ACTIONPROGRESSWIDGET_H
