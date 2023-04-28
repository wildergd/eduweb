#ifndef ITEMCONFIGBUTTON_H
#define ITEMCONFIGBUTTON_H

#include <QVariant>
#include <QPushButton>

class ItemConfigButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ItemConfigButton(QWidget* parent = 0);
    QVariant data() const;
    void setData(QVariant value);

private:
    QVariant buttonData;

signals:
    void onButtonClicked(ItemConfigButton* button);

public slots:
    void onButtonClick();
};

#endif // ITEMCONFIGBUTTON_H
