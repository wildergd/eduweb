#include "plugindetailsdialog.h"
#include "ui_plugindetailsdialog.h"

PluginDetailsDialog::PluginDetailsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginDetailsDialog)
{
    ui->setupUi(this);
	retranslateUI();
	
	/* configure widgets */
    ui->fldPluginCopyright->setTextFormat(Qt::RichText);
	
	/* configure signals */
    connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

PluginDetailsDialog::~PluginDetailsDialog()
{
    delete ui;
}

void PluginDetailsDialog::retranslateUI()
{
    ui->lbPluginName->setText(trUtf8("Name:"));
    ui->lbPluginVersion->setText(trUtf8("Version:"));
    ui->lbPluginAuthor->setText(trUtf8("Author(s):"));
    ui->lbPluginVendor->setText(trUtf8("Vendor:"));
    ui->lbPluginUrl->setText(trUtf8("Url:"));
    ui->lbPluginDescription->setText(trUtf8("Description:"));
    ui->lbPluginCopyright->setText(trUtf8("Copyright:"));
    ui->lbPluginLicense->setText(trUtf8("License:"));
    ui->lbPluginDependencies->setText(trUtf8("Dependencies:"));

    ui->closeBtn->setText(trUtf8("Close"));
}

void PluginDetailsDialog::updateContents(IPlugin* plugin)
{
    if (plugin)
    {
        ui->fldPluginName->setText(plugin->pluginName());
        ui->fldPluginVersion->setText(plugin->pluginVersion());
        ui->fldPluginAuthor->setText(plugin->pluginAuthor());
        ui->fldPluginVendor->setText(plugin->pluginVendor());
        ui->fldPluginUrl->setText(plugin->pluginUrl());
        ui->fldPluginDescription->setPlainText(plugin->pluginDescription());
        ui->fldPluginCopyright->setText(plugin->pluginCopyright());
        ui->fldPluginLicense->setPlainText(plugin->pluginLicense());
        ui->fldPluginDependencies->addItems(plugin->pluginDependencies());
        ui->fldPluginDependencies->setSelectionMode(QAbstractItemView::NoSelection);
    }
}
