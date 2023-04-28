#include "fileselectwidget.h"
#include "ui_fileselectwidget.h"

FileSelectWidget::FileSelectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSelectWidget)
{
    ui->setupUi(this);

    /* configure widgets */
    dialogTitle = trUtf8("Open file");
    selectedFilter = trUtf8("All Files") + "(*.*)";
    dialogType = DialogOpen;

    switch (dialogType)
    {
    case DialogOpen:
        ui->launchBtn->setIcon(QIcon(QPixmap(":/icons/document-open.png")));
        break;
    case DialogSave:
        ui->launchBtn->setIcon(QIcon(QPixmap(":/icons/media-floppy.png")));
        break;
    }

    /* configure signals */
    connect(ui->launchBtn, SIGNAL(clicked()), this, SLOT(launchDialog()));
}

FileSelectWidget::~FileSelectWidget()
{
    delete ui;
}

QString FileSelectWidget::fileName() const
{
    return ui->textEdit->text();
}

QString FileSelectWidget::caption() const
{
    return dialogTitle;
}

QString FileSelectWidget::filter() const
{
    return selectedFilter;
}

DialogType FileSelectWidget::type() const
{
    return dialogType;
}

void FileSelectWidget::setDialogType(DialogType dlgType)
{
    dialogType = dlgType;
}

void FileSelectWidget::setCaption(const QString value)
{
    dialogTitle = value;
}

void FileSelectWidget::setFilter(const QString value)
{
    selectedFilter = value;
}

void FileSelectWidget::launchDialog()
{
    switch(dialogType)
    {
    case DialogOpen:
        launchFileOpenDialog();
        break;
    case DialogSave:
        launchFileSaveDialog();
        break;
    }
}

void FileSelectWidget::launchFileSaveDialog()
{
    QString selectedFile = QFileDialog::getSaveFileName(0, caption(), QDir::homePath(), filter());

    if (!selectedFile.isEmpty() || !selectedFile.isNull())
    {
        ui->textEdit->setText(selectedFile);
        emit fileChanged();
    }
}

void FileSelectWidget::launchFileOpenDialog()
{
    QString selectedFile = QFileDialog::getOpenFileName(0, caption(), QDir::homePath(), filter());

    if (!selectedFile.isEmpty() || !selectedFile.isNull())
    {
        ui->textEdit->setText(selectedFile);
        emit fileChanged();
    }
}
