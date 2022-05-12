#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
double CalcVal = 0.0 ;
bool AddTrigger = false ;
bool MultTrigger = false;
bool DivTrigger = false;
bool SquareTrigger = false;
bool SubTrigger = false;
bool ModTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(CalcVal));
    QPushButton *numButton[10];
    for(int i = 0;i < 10;i++){
        QString butname = "Button"+QString::number(i);
        numButton[i] = MainWindow::findChild<QPushButton *>(butname);
        connect(numButton[i],SIGNAL(released()),this,SLOT(NumberPressed()));
    }

    connect(ui->Add,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Subs,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Mult,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Mod,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Square,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Equal,SIGNAL(released()),this,SLOT(EqualButton()));
    connect(ui->Sign,SIGNAL(released()),this,SLOT(ChangeSign()));
    connect(ui->Del,SIGNAL(released()),SLOT(RemoveNumber()));
    connect(ui->Dot,SIGNAL(released()),SLOT(AddDot()));
    connect(ui->Flush,SIGNAL(released()),SLOT(ClearDisplay()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::FlushDisplay(QString preview){
    ui->Memory3->setText(ui->Memory2->text());
    ui->Memory2->setText(ui->Memory1->text());
    ui->Memory1->setText(preview);
}
void MainWindow::NumberPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){
        ui->Display->setText(buttonVal);
    }else{
        QString newVal = displayVal + buttonVal;
        double newDoubleVal = newVal.toDouble();
        ui->Display->setText(QString::number(newDoubleVal,'g',16));
    }
}

void MainWindow::MathButtonPressed(){
    AddTrigger = false ;
    MultTrigger = false;
    DivTrigger = false;
    SquareTrigger = false;
    SubTrigger = false;
    ModTrigger = false;
    QString displayVal = ui->Display->text();
    CalcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"÷",Qt::CaseInsensitive) == 0){
        DivTrigger = true;
    }else if(QString::compare(butVal,"+",Qt::CaseInsensitive) == 0){
        AddTrigger = true;
    }else if(QString::compare(butVal,"-",Qt::CaseInsensitive) == 0){
        SubTrigger = true;
    }else if(QString::compare(butVal,"x",Qt::CaseInsensitive) == 0){
        MultTrigger = true;
    }else if(QString::compare(butVal,"%",Qt::CaseInsensitive) == 0){
        ModTrigger = true;
    }else if(QString::compare(butVal,"√",Qt::CaseInsensitive) == 0){
        SquareTrigger = true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButton(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    QString Operator;
    double dblDisplayVal = displayVal.toDouble();
    if(DivTrigger || AddTrigger || SubTrigger || MultTrigger || ModTrigger || SquareTrigger){
        if(AddTrigger){
            solution = CalcVal + dblDisplayVal;
            Operator = '+';
        }else if(SubTrigger){
            solution = CalcVal - dblDisplayVal;
            Operator = '-';
        }else if(MultTrigger){
            solution = CalcVal * dblDisplayVal;
            Operator = 'x';
        }else if(DivTrigger){
            solution = CalcVal / dblDisplayVal;
            Operator = '÷';
        }else if(ModTrigger){
            solution = int(CalcVal) % int(dblDisplayVal);
            Operator = '%';
        }else if(SquareTrigger){
            solution = sqrt(dblDisplayVal);
        }
    }
    QString OperatorDisplay = QString::number(CalcVal) + " " +Operator+ " " + displayVal + " = " +QString::number(solution);
    MainWindow::FlushDisplay(OperatorDisplay);
    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeSign(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double invDblDisplayVal = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(invDblDisplayVal));
    }
}

void MainWindow::RemoveNumber(){
    QString DisplayVal = ui->Display->text();
    QString NewDisplayVal = DisplayVal.mid(0,DisplayVal.size()-1);
    ui->Display->setText(NewDisplayVal);
}
void MainWindow::AddDot(){
    QString DisplayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9]*");
    if(reg.exactMatch(DisplayVal)){
        QString NewDisplayVal = DisplayVal+".";
        ui->Display->setText(NewDisplayVal);
    }
}
void MainWindow::ClearDisplay(){
    ui->Display->setText("");
}


