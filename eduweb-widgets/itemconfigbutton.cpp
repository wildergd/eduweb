#include "itemconfigbutton.h"

ItemConfigButton::ItemConfigButton(QWidget* parent) :
    QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(onButtonClick()));
}

QVariant ItemConfigButton::data() const
{
    return buttonData;
}

void ItemConfigButton::setData(QVariant value)
{
    buttonData = value;
}

void ItemConfigButton::onButtonClick()
{
    emit onButtonClicked(this);
}
