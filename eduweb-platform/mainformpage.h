#ifndef MAINFORMPAGE_H
#define MAINFORMPAGE_H

#include <QWidget>
#include "mainwindow.h"

class MainFormPage: public QWidget
{
    Q_OBJECT
	
public:
    MainFormPage(QWidget* parent = 0);
    virtual void updateContents() = 0;
    virtual void retranslateUI() = 0;

    void setParentForm(MainWindow* form);

protected:
    MainWindow* parentForm;

};

#endif // MAINFORMPAGE_H
