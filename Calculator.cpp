#include "Calculator.h"
#include "./ui_Calculator.h"
#include <QObject>//
#include <QRegularExpression>

enum MathOperation
{
    nothing, add, substract, multiply, divide
};
MathOperation mathops = nothing;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent),ui(new Ui::Calculator)
    , currentValue(0)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(currentValue));
    QPushButton *myButtons[10];

    for(int i = 0; i < 10; i++)
    {
        QString buttonName = "PushButton" + QString::number(i);
        myButtons[i]= Calculator::findChild<QPushButton*>(buttonName);
        //connect()
        connect(myButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Substract, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeSignPressed()));




}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *buttonPressed = dynamic_cast<QPushButton *>(sender());
    if(buttonPressed)
    {
        QString buttonText = buttonPressed->text();
        //get the display text
        QString ValueText = ui->Display->text();

        if(ValueText.toDouble() == 0 || ValueText.toDouble() == 0.0)
            ui->Display->setText(buttonText);
        else
        {
            QString valueToDisplay = ValueText + buttonText;
            //change it to double
            double dblValue = valueToDisplay.toDouble();
            //change it back to string
            ui->Display->setText(QString::number(dblValue, 'g', 16));
        }

    }

}

void Calculator::MathButtonPressed()
{
    QPushButton* buttonPressed = dynamic_cast<QPushButton*>(sender());
    if(buttonPressed)
    {
        mathops = nothing;
        QString buttonText = buttonPressed->text();
        QString ValueText = ui->Display->text();
        currentValue = ValueText.toDouble();
        QString mathSymbol ="";
        if(QString::compare(buttonText,"*", Qt::CaseInsensitive) == 0)
        {
            mathops = multiply;
            mathSymbol = "*";
        }
        else if(QString::compare(buttonText,"/", Qt::CaseInsensitive) == 0)
        {
            mathops = divide;
            mathSymbol = "/";
        }
        else if(QString::compare(buttonText,"-", Qt::CaseInsensitive) == 0)
        {
            mathops = substract;
            mathSymbol = "-";
        }
        else{
            mathops = add;
            mathSymbol = "+";
        }

        ui->Display->setText(ValueText + " " + mathSymbol);
    }

}

void Calculator::EqualButtonPressed()
{
    //get current value
    QString valueText = ui->Display->text();
    double value = valueText.toDouble();
    switch (mathops) {
    case add:
        currentValue += value;
        break;
    case substract:
        currentValue -= value;
        break;
    case multiply:
        currentValue *= value;
        break;
    case divide:
        currentValue /= value;
        break;

    default:
        break;
    }
    ui->Display->setText(QString::number(currentValue));
}

void Calculator::ChangeSignPressed()
{
    QString valueText = ui->Display->text();
    QRegularExpression myReg("[-]?[0-9.]*");

    if(myReg.match(valueText).hasMatch())
    {
        double valDouble = -1* valueText.toDouble();
        ui->Display->setText(QString::number(valDouble));
    }

}
