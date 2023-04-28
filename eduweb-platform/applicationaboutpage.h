#ifndef APPLICATIONABOUTPAGE_H
#define APPLICATIONABOUTPAGE_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "mainformpage.h"

namespace Ui {
    class ApplicationAboutPage;
}

class ApplicationAboutPage : public MainFormPage
{
    Q_OBJECT

public:
    explicit ApplicationAboutPage(QWidget *parent = 0);
    ~ApplicationAboutPage();
    void updateContents();
    void retranslateUI();

protected:
    void showEvent(QShowEvent * event);

private slots:
	void onPluginClick(QTreeWidgetItem* item, int column);

private:
    Ui::ApplicationAboutPage *ui;
};

#endif // APPLICATIONABOUTPAGE_H
