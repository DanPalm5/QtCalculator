#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);


    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++){
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(buttonName);

        // "connect" the NumPressed slot (event handler) with the released() signal (event)
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    // do the same for each of the math buttons
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble()==0) || (displayVal.toDouble()==0.0)){
        ui->Display->setText(buttonValue);
    }else{
        QString newValue = displayVal + buttonValue;
        double newDoubleValue = newValue.toDouble();
        ui->Display->setText(QString::number(newDoubleValue, 'g', 16));
    }
}


void Calculator::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayValue = ui->Display->text();
    calcVal = displayValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    if(QString::compare(buttonValue, "/", Qt::CaseInsensitive)==0){
        divTrigger = true;
    } else if(QString::compare(buttonValue, "*", Qt::CaseInsensitive)==0){
        multTrigger = true;
    } else if(QString::compare(buttonValue, "+", Qt::CaseInsensitive)==0){
        addTrigger = true;
    } else{
        subTrigger = true;
    }
    ui->Display->setText("");

}


void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayValue = ui->Display->text();
    double doubleDisplayValue = displayValue.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + doubleDisplayValue;
        } else if(subTrigger){
            solution = calcVal - doubleDisplayValue;
        } else if(multTrigger){
            solution = calcVal * doubleDisplayValue;
        } else{
            solution = calcVal / doubleDisplayValue;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegularExpression regExp("[-]?[0-9.]*");
    QRegularExpressionMatch match = regExp.match(displayVal);

    if(match.hasMatch()){
        double doubleDisplayVal = displayVal.toDouble();
        double doubleDisplalValSign = -1* doubleDisplayVal;
        ui->Display->setText(QString::number(doubleDisplalValSign));
    }
}

void Calculator::ClearButtonPressed(){
    ui->Display->setText("0");
}

