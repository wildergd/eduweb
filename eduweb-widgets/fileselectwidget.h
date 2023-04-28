#ifndef FILESELECTWIDGET_H
#define FILESELECTWIDGET_H

#include <QWidget>
#include <QFileDialog>
#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
#include <QtDesigner/QDesignerExportWidget>
#endif

typedef enum {
    DialogSave,
    DialogOpen
} DialogType;

namespace Ui {
    class FileSelectWidget;
}

#if defined(EDUWEB_WIDGETS_QTDESIGNER_LIBRARY)
class QDESIGNER_WIDGET_EXPORT FileSelectWidget : public QWidget
#else
class FileSelectWidget : public QWidget
#endif
{
    Q_OBJECT
    Q_PROPERTY(QString file READ fileName)

public:
    explicit FileSelectWidget(QWidget *parent = 0);
    ~FileSelectWidget();

    QString caption() const;
    QString fileName() const;
    QString filter() const;
    DialogType type() const;

    void setCaption(const QString value);
    void setFilter(const QString value);
    void setDialogType(DialogType dlgType);

private:
    Ui::FileSelectWidget *ui;

    QString selectedFilter;
    QString dialogTitle;
    QFileDialog::Options dialogOption;
    DialogType dialogType;

    void launchFileOpenDialog();
    void launchFileSaveDialog();

private slots:
    void launchDialog();

signals:
    void fileChanged();
};

#endif // FILESELECTWIDGET_H
