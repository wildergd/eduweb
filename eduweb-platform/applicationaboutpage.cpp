#include "applicationaboutpage.h"
#include "ui_applicationaboutpage.h"
#include "plugindetailsdialog.h"
#include "pluginmanager.h"

ApplicationAboutPage::ApplicationAboutPage(QWidget *parent) :
    MainFormPage(parent),
    ui(new Ui::ApplicationAboutPage)
{
    /* configure widgets */
    ui->setupUi(this);

    ui->pluginsList->header()->setResizeMode(0, QHeaderView::ResizeToContents);
	ui->pluginsList->header()->setResizeMode(1, QHeaderView::ResizeToContents);
	ui->pluginsList->header()->setResizeMode(2, QHeaderView::Stretch);
	ui->pluginsList->header()->setMovable(false);

    retranslateUI();

    /* configure signals */
	connect(ui->pluginsList, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onPluginClick(QTreeWidgetItem*,int)));
}

ApplicationAboutPage::~ApplicationAboutPage()
{
    delete ui;
}

void ApplicationAboutPage::retranslateUI()
{
    ui->retranslateUi(this);
/*	ui->lbAboutApp->setText(trUtf8("About eduWeb") + " 1.1");
	ui->lbAppCredits->setText("<p>" + trUtf8("eduWeb is an author tool oriented  to professors without programming knowledge and it is based on the curricular structuring and didactic conduction of the education.") + "</p><p>&copy; 2009 " + trUtf8("All rights reserved to the authors") + "</p>");
	ui->lbAboutInstalledPlugins->setText(trUtf8("About installed plugins"));
	ui->pluginsList->headerItem()->setText(0, "Plugin");
	ui->pluginsList->headerItem()->setText(1, trUtf8("Version"));
    ui->pluginsList->headerItem()->setText(2, trUtf8("Description"));*/
}

void ApplicationAboutPage::updateContents()
{
    ui->pluginsList->clear();
    foreach (IPlugin* plugin, PluginManager::instance()->plugins())
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setTextAlignment(1, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        item->setText(0, plugin->pluginName());
        item->setText(1, plugin->pluginVersion());
        item->setText(2, plugin->pluginDescription());
        
		item->setData(0, Qt::UserRole, QVariant::fromValue(plugin->pluginName()));
        ui->pluginsList->addTopLevelItem(item);
    }
}

void ApplicationAboutPage::showEvent(QShowEvent * event)
{
        Q_UNUSED(event);
}

void ApplicationAboutPage::onPluginClick(QTreeWidgetItem* item, int column)
{
    QString pluginId = item->data(0, Qt::UserRole).toString();

    PluginDetailsDialog dlgPluginInfo;
    dlgPluginInfo.updateContents(PluginManager::instance()->plugins().value(pluginId));
    dlgPluginInfo.exec();
}
