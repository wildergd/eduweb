#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setWidgetsEnabled(bool enabled);

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
//    void configParamValueChanged(const QString paramName); 

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
