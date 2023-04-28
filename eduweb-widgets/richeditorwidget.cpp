#include <QTextCursor>
#include <QTextList>
#include <QTextListFormat>
#include "richeditorwidget.h"
#include "ui_richeditorwidget.h"

RichEditorWidget::RichEditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RichEditorWidget)
{
    /* configure widgets */
    ui->setupUi(this);
    document = ui->editor->document();
	
	/* configure signals */
	connect(ui->btnSetTextBold, SIGNAL(toggled(bool)), this, SLOT(toggleBold(bool)));
	connect(ui->btnSetTextItalic, SIGNAL(toggled(bool)), this, SLOT(toggleItalic(bool)));
	connect(ui->btnSetTextUnderline, SIGNAL(toggled(bool)), this, SLOT(toggleUnderline(bool)));

	connect(ui->editor, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)), this, SLOT(currentCharFormatChanged(const QTextCharFormat &)));
	connect(ui->editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChanged()));

	connect(ui->btnSetTextAlignLeft, SIGNAL(clicked()), this, SLOT(textAlignLeft()));
	connect(ui->btnSetTextAlignCenter, SIGNAL(clicked()), this, SLOT(textAlignCenter()));
	connect(ui->btnSetTextAlignRight, SIGNAL(clicked()), this, SLOT(textAlignRight()));
	connect(ui->btnSetTextAlignJustify, SIGNAL(clicked()), this, SLOT(textAlignJustify()));

	connect(ui->btnSetTextBulletList, SIGNAL(clicked()), this, SLOT(toggleBulletedList()));
	connect(ui->btnSetTextNumberedList, SIGNAL(clicked()), this, SLOT(toggleNumberedList()));

	connect(ui->editor, SIGNAL(textChanged()), this, SLOT(editorTextChanged()));
}

RichEditorWidget::~RichEditorWidget()
{
    delete ui;
}

QTextEdit* RichEditorWidget::textEditor()
{
	return ui->editor;
}

QString RichEditorWidget::text()
{
    QString text = document->toHtml("utf-8");
	QRegExp regExp("<body([^>]*)>\\n(.*)</body>");
	if (regExp.indexIn(text))
		text = regExp.cap(2);

	text.replace(QRegExp("<([^/][a-z|A-Z|0-9]*)([^>]*)>"), "<\\1>");
	text.replace(QRegExp("<([^/][a-z|A-Z|0-9]*)></([a-z|A-Z|0-9]*)>"), "");
	text.replace(QRegExp("<table>"), "<table border=\"1\" cellpadding=\"5\" cellspacing=\"2\">");

	return text;
}

void RichEditorWidget::setText(QString value)
{
    QTextCursor cursor = ui->editor->textCursor();
	cursor.clearSelection();
	ui->editor->clear();
	ui->editor->setTextCursor(cursor);
	ui->editor->setHtml("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n<html xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n\t<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n\t<title></title>\n\t<style type=\"text/css\" rel=\"stylesheet\">\n\t\ttable {\n\t\t\tborder:1px solid #000;\n\t\t}\n\t\ttable td {\n\t\t\tborder:1px solid #000;\n\t\t}\n\t</style>\n</head>\n<body>\n" + value + "</body>\n</html>");
}

void RichEditorWidget::toggleBold(bool checked)
{
	QTextCharFormat fmt;
	fmt.setFontWeight((checked) ? QFont::Bold : QFont::Normal);
	mergeFormatOnWordOrSelection(fmt);
	ui->editor->setFocus();
}

void RichEditorWidget::toggleItalic(bool checked)
{
	QTextCharFormat fmt;
	fmt.setFontItalic(checked);
	mergeFormatOnWordOrSelection(fmt);
	ui->editor->setFocus();
}

void RichEditorWidget::toggleUnderline(bool checked)
{
	QTextCharFormat fmt;
	fmt.setFontUnderline(checked);
	mergeFormatOnWordOrSelection(fmt);
	ui->editor->setFocus();
}

void RichEditorWidget::textAlignLeft()
{
	ui->editor->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
	ui->editor->setFocus();
}

void RichEditorWidget::textAlignCenter()
{
	ui->editor->setAlignment(Qt::AlignHCenter);
	ui->editor->setFocus();
}

void RichEditorWidget::textAlignRight()
{
	ui->editor->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
	ui->editor->setFocus();
}

void RichEditorWidget::textAlignJustify()
{
	ui->editor->setAlignment(Qt::AlignJustify);
	ui->editor->setFocus();
}

void RichEditorWidget::currentCharFormatChanged(const QTextCharFormat &format)
{
	fontChanged(format.font());
}

void RichEditorWidget::cursorPositionChanged()
{
	alignmentChanged(ui->editor->alignment());
	cursorListChanged();
}

void RichEditorWidget::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
	QTextCursor cursor = ui->editor->textCursor();
	if (!cursor.hasSelection())
		cursor.select(QTextCursor::WordUnderCursor);
	cursor.mergeCharFormat(format);
	ui->editor->mergeCurrentCharFormat(format);
}

void RichEditorWidget::fontChanged(const QFont &f)
{
	ui->btnSetTextBold->setChecked(f.bold());
	ui->btnSetTextItalic->setChecked(f.italic());
	ui->btnSetTextUnderline->setChecked(f.underline());
}

void RichEditorWidget::alignmentChanged(Qt::Alignment a)
{
	if (a & Qt::AlignLeft)
	{
		ui->btnSetTextAlignLeft->setChecked(true);
	}
	else if (a & Qt::AlignHCenter)
	{
		ui->btnSetTextAlignCenter->setChecked(true);
	}
	else if (a & Qt::AlignRight)
	{
		ui->btnSetTextAlignRight->setChecked(true);
	}
	else if (a & Qt::AlignJustify)
	{
		ui->btnSetTextAlignJustify->setChecked(true);
	}
}

void RichEditorWidget::cursorListChanged()
{
	QTextCursor cursor = ui->editor->textCursor();

	cursor.beginEditBlock();

	if (QTextList* list = cursor.currentList())
	{
		ui->btnSetTextNumberedList->setChecked(list->format().style() == QTextListFormat::ListDecimal);
		ui->btnSetTextBulletList->setChecked(list->format().style() == QTextListFormat::ListDisc);
	}
	else
	{
		ui->btnSetTextNumberedList->setChecked(false);
		ui->btnSetTextBulletList->setChecked(false);
	}

	cursor.endEditBlock();
}

void RichEditorWidget::toggleBulletedList()
{
	QTextCursor cursor = ui->editor->textCursor();

	if (ui->btnSetTextNumberedList->isChecked())
	{
		ui->btnSetTextNumberedList->setChecked(false);
	}

	if (ui->btnSetTextBulletList->isChecked())
	{
		cursor.beginEditBlock();
		QTextBlockFormat blockFmt = cursor.blockFormat();
		QTextListFormat listFmt;

		if (cursor.currentList())
		{
			listFmt = cursor.currentList()->format();
		}
		else
		{
			listFmt.setIndent(blockFmt.indent() + 1);
			blockFmt.setIndent(0);
			cursor.setBlockFormat(blockFmt);
		}

		listFmt.setStyle(QTextListFormat::ListDisc);
		cursor.createList(listFmt);
		cursor.endEditBlock();
	}
	else
	{
		QTextBlockFormat blockFmt = cursor.blockFormat();
		blockFmt.setObjectIndex(-1);
		cursor.setBlockFormat(blockFmt);
	}

	ui->editor->setFocus();
}

void RichEditorWidget::toggleNumberedList()
{
	QTextCursor cursor = ui->editor->textCursor();

	if (ui->btnSetTextBulletList->isChecked())
	{
		ui->btnSetTextBulletList->setChecked(false);
	}

	if (ui->btnSetTextNumberedList->isChecked())
	{
		cursor.beginEditBlock();
		QTextBlockFormat blockFmt = cursor.blockFormat();
		QTextListFormat listFmt;

		if (cursor.currentList())
		{
			listFmt = cursor.currentList()->format();
		}
		else
		{
			listFmt.setIndent(blockFmt.indent() + 1);
			blockFmt.setIndent(0);
			cursor.setBlockFormat(blockFmt);
		}

		listFmt.setStyle(QTextListFormat::ListDecimal);
		cursor.createList(listFmt);
		cursor.endEditBlock();
	}
	else
	{
		QTextBlockFormat blockFmt = cursor.blockFormat();
		blockFmt.setObjectIndex(-1);
		cursor.setBlockFormat(blockFmt);
	}

	ui->editor->setFocus();
}

void RichEditorWidget::editorTextChanged()
{
	emit textChanged();
}
