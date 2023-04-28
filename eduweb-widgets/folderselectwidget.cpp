#include "folderselectwidget.h"
#include "ui_folderselectwidget.h"

FolderSelectWidget::FolderSelectWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FolderSelectWidget)
{
    ui->setupUi(this);

    /* configure widgets */
    dialogTitle = trUtf8("Open folder");

    /* configure signals */
    connect(ui->launchBtn, SIGNAL(clicked()), this, SLOT(launchFileOpenDialog()));
}

FolderSelectWidget::~FolderSelectWidget()
{
    delete ui;
}

QString FolderSelectWidget::folder() const
{
    return currentFolder;
}

QString FolderSelectWidget::caption() const
{
    return dialogTitle;
}

void FolderSelectWidget::setCaption(const QString value)
{
    dialogTitle = value;
}

void FolderSelectWidget::setFolder(const QString value)
{
    currentFolder = value;
    ui->textEdit->setText(value);
}

void FolderSelectWidget::launchFileOpenDialog()
{
    QString startFolder = (!currentFolder.isEmpty()) ? currentFolder : QDir::homePath();
    QString selectedFolder = QFileDialog::getExistingDirectory(0, caption(), startFolder);
    if (!selectedFolder.isEmpty() || !selectedFolder.isNull())
    {
        ui->textEdit->setText(selectedFolder);
        currentFolder = selectedFolder;
        emit folderChanged();
    }
}
