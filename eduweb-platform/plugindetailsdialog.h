#ifndef PLUGINDETAILSDIALOG_H
#define PLUGINDETAILSDIALOG_H

#include <QDialog>
#include "iplugin.h"

namespace Ui {
    class PluginDetailsDialog;
}

class PluginDetailsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PluginDetailsDialog(QWidget *parent = 0);
    ~PluginDetailsDialog();
    void retranslateUI();
    void updateContents(IPlugin* plugin);

private:
    Ui::PluginDetailsDialog *ui;
};

#endif // PLUGINDETAILSDIALOG_H
