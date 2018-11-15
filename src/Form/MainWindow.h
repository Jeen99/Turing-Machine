#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../MT/MT.h"
#include <string>


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT                                    //макрос для Qt
    Turing::MT* turing;                         //создаем указатель на экземпляр класса Машина Тюринга
    bool start = false;                         //состояние запуска машины
    std::string DisplayText;                    //отображаемый текст

public:
    explicit MainWindow(QWidget *parent = 0);   //конструктор окна
    ~MainWindow();

private slots:

    void on_BtStart_clicked();                  //кнопка старт
    void on_BtReset_clicked();                  //кнопка рестарт

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
