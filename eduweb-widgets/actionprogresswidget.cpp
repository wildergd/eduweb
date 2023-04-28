#include "actionprogresswidget.h"
#include "ui_actionprogresswidget.h"

ActionProgressWidget::ActionProgressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionProgressWidget)
{
    ui->setupUi(this);
	
	/* customize widgets */
	ui->progressBar->reset();
}

ActionProgressWidget::~ActionProgressWidget()
{
    delete ui;
}

QProgressBar * ActionProgressWidget::progressBar()
{
	return ui->progressBar;
}

void ActionProgressWidget::setLabel(const QString value)
{
	ui->label->setText(value);
}
