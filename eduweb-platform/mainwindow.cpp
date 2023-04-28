#include <QDesktopWidget>
#include <QMessageBox>
#include <QApplication>
#include <QPalette>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainformpage.h"
#include "myprojectspage.h"
#include "newprojectpage.h"
#include "deployprojectspage.h"
#include "applicationsettingspage.h"
#include "applicationaboutpage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("eduWeb 1.1");
    setObjectName("MainForm");
    resize(740, 506);

    /* position window in the center of the screen */
    QDesktopWidget *desktop = QApplication::desktop();
    QRect desktopSize = desktop->availableGeometry(desktop->primaryScreen());
    int x = (desktopSize.width() - width()) / 2;
    int y = (desktopSize.height() - height()) / 2;
    move(x, y);

    /* initializing menu */
    ui->optionsList->setIconSize(QSize(64, 64));
    ui->optionsList->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->optionsList->setProperty("showDropIndicator", QVariant(false));

    /* initializing pages */
	MyProjectsPage* myProjectsPage = new MyProjectsPage;
	myProjectsPage->setParentForm(this);
	ui->pages->insertWidget(0, myProjectsPage);

	NewProjectPage* newProjectPage = new NewProjectPage;
	newProjectPage->setParentForm(this);
	ui->pages->insertWidget(1, newProjectPage);

	DeployProjectsPage* deployPage = new DeployProjectsPage;
	deployPage->setParentForm(this);
	ui->pages->insertWidget(2, deployPage);

	ApplicationSettingsPage * optionsPage = new ApplicationSettingsPage;
	optionsPage->setParentForm(this);
	ui->pages->insertWidget(3, optionsPage);

	ApplicationAboutPage * aboutPage = new ApplicationAboutPage;
	aboutPage->setParentForm(this);
	ui->pages->insertWidget(4, aboutPage);

    /* event handlers */
    connect(ui->optionsList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(changePage(QListWidgetItem *, QListWidgetItem*)));
    connect(ui->optionsList, SIGNAL(configParamValueChanged(QString)), this, SLOT(configParamValueChanged(QString)));

    // initialize
    ui->optionsList->setCurrentRow(0);
    ui->retranslateUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWidgetsEnabled(bool enabled)
{
	ui->optionsList->setEnabled(enabled);
	ui->optionsList->setDisabled(!enabled);
	ui->optionsList->updatesEnabled();

	ui->pages->setEnabled(enabled);
	ui->pages->setDisabled(!enabled);
	ui->pages->updatesEnabled();
}

void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;

	ui->pages->setCurrentIndex(ui->optionsList->row(current));
	if(MainFormPage *page = qobject_cast<MainFormPage*>(ui->pages->currentWidget()))
	{
		page->updateContents();
	}
}
