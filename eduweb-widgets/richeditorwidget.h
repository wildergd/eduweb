#ifndef RICHEDITORWIDGET_H
#define RICHEDITORWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QTextDocument>
#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
#include <QtDesigner/QDesignerExportWidget>
#endif

namespace Ui {
    class RichEditorWidget;
}

#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
class QDESIGNER_WIDGET_EXPORT RichEditorWidget : public QWidget
#else
class RichEditorWidget : public QWidget
#endif
{
    Q_OBJECT
	Q_PROPERTY(QString text READ text WRITE setText)

public:
    explicit RichEditorWidget(QWidget *parent = 0);
    ~RichEditorWidget();
	QTextEdit* textEditor();
	QString text();
	void setText(QString value);

private:
    Ui::RichEditorWidget *ui;
    QTextDocument* document;

	void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
	void fontChanged(const QFont &f);
	void alignmentChanged(Qt::Alignment a);
	void cursorListChanged();

private slots:
	void toggleBold(bool checked);
	void toggleItalic(bool checked);
	void toggleUnderline(bool checked);

	void currentCharFormatChanged(const QTextCharFormat &format);
	void cursorPositionChanged();

	void textAlignLeft();
	void textAlignCenter();
	void textAlignRight();
	void textAlignJustify();

	void toggleBulletedList();
	void toggleNumberedList();

	void editorTextChanged();

signals:
	void textChanged();
};

#endif // RICHEDITORWIDGET_H
