#include "QtWidgetsApplication1.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void QtWidgetsApplication1::PushButtonClicked()
{
    QString pushButtonShowText = "You Has Been Clicked The Push Button!!!";
    ui.lineEdit->setText(pushButtonShowText);
}
