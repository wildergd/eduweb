#ifndef FOLDERSELECTWIDGET_H
#define FOLDERSELECTWIDGET_H

#include <QWidget>
#include <QFileDialog>
#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
#include <QtDesigner/QDesignerExportWidget>
#endif

namespace Ui {
    class FolderSelectWidget;
}

#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
class QDESIGNER_WIDGET_EXPORT FolderSelectWidget : public QWidget
#else
class FolderSelectWidget : public QWidget
#endif
{
    Q_OBJECT
    Q_PROPERTY(QString folder READ folder)

public:
    explicit FolderSelectWidget(QWidget *parent = 0);
    ~FolderSelectWidget();

    QString folder() const;
    QString caption() const;

    void setCaption(const QString value);
    void setFolder(const QString value);
    QString dialogTitle;
    QFileDialog::Options dialogOption;
    QString currentFolder;

private slots:
    void launchFileOpenDialog();

signals:
    void folderChanged();

private:
    Ui::FolderSelectWidget *ui;
};

#endif // FOLDERSELECTWIDGET_H
