#ifndef APPLICATIONSETTINGSPAGE_H
#define APPLICATIONSETTINGSPAGE_H

#include <QWidget>
#include "mainformpage.h"

namespace Ui {
    class ApplicationSettingsPage;
}

class ApplicationSettingsPage : public MainFormPage
{
    Q_OBJECT

public:
    explicit ApplicationSettingsPage(QWidget *parent = 0);
    ~ApplicationSettingsPage();
    void updateContents();
    void retranslateUI();

protected:
    void showEvent(QShowEvent * event);

signals:
	void configParamValueChanged(const QString paramName);

private slots:
	void styleChanged(const QString & text);
	void languageChanged(int index);
    void workspaceFolderChanged();

private:
    Ui::ApplicationSettingsPage *ui;
};

#endif // APPLICATIONSETTINGSPAGE_H
