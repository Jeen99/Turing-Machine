#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <string>
#include "ChangeColor.h"

static const std::string RulePath = "rule.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)           //конструктор окна
{
    ui->setupUi(this);
    turing = new Turing::MT();
    turing->loadRule(RulePath);
    DisplayText = "";
}

MainWindow::~MainWindow()           //деструктор окна
{
    delete ui;
}

void MainWindow::on_BtStart_clicked()                               //старт
{
    if (!start)
    {
        std::string temp;
        temp= ui->lineEdit_Mem->text().toStdString();               //получаем введенную строку и
        turing->setMem(temp);                                       //передаем объекту

        temp = ui->lineEdit_State->text().toStdString();            //получаем введенное состояние
        turing->setState(temp);                                     //передаем объекту

        ui->lineEdit_Mem->setDisabled(true);                        //отключаем поля ввода
        ui->lineEdit_State->setDisabled(true);                      //отключаем поля ввода
    }

    DisplayText += "State: " + turing->getState() + ' ';            //добавляем информацию для отображения

    DisplayText += ChangeColor(turing->getMem(), turing->getPosition());
    DisplayText += "<br/>";


    ui->textBrowser->setText(QString::fromStdString(DisplayText));  //вывод информации
    turing->step();                                                 //выполняем шаг

    start = true;

    QTextCursor cur(ui->textBrowser->document());                    //для скрола текста вниз
    cur.movePosition(QTextCursor::End);
    ui->textBrowser->setTextCursor(cur);
}

void MainWindow::on_BtReset_clicked()                               //сброс
{
    start = false;
    DisplayText.clear();                                            //очистка информации
    ui->textBrowser->clear();                                       //очистка интерфейса
    ui->lineEdit_Mem->setDisabled(false);                           //отключаем поля ввода
    ui->lineEdit_State->setDisabled(false);

    if (ui->checkResetRule->isChecked())
       turing->loadRule(RulePath);
}
