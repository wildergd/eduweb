#include "mainformpage.h"

MainFormPage::MainFormPage(QWidget* parent)
    :QWidget(parent)
{
}


void MainFormPage::setParentForm(MainWindow* form)
{
        parentForm = form;
}

