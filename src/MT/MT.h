#ifndef MT_H
#define MT_H

#include <string>
#include <fstream>
#include <vector>

namespace Turing {

using std::string;              //использование пространств имен
using std::ifstream;            //для использования стринга, ифстрима и вектора
using std::vector;

class MT
{
    enum { R = 1, L = -1, H = 0 };	//перечисление направлений

    struct State					//структура состояния
    {
        string q;
        char sym;
    };

    struct Rule                     // структура правила
    {
        string curQ;				// текущее состояние
        string nextQ;				// следующее состояние
        char curSym;				// текущий символ
        char nextSym;				// следующий символ
        char cmd;					// команда на перемещение
    };

public:
    MT(void);					// конструктор

    void setState(string state);// установить состояние
    void setMem(string mem);    // получение ленты

    string getState()const;		// получение текущего состояния
    string getMem() const;		// получение содержимого ленты
    char getSym()const;			// получение символа из тек. позиции
    int getPosition() const;

    void addRule(string rule);	// добавление правила
    void loadRule(string path); // загрузка правил из файла
    void step();				// шаг машины


private:
    void process(int i);
    string mem;					// содержимое ленты
    static const int width = 2;	// ширина поля записи состояния
    int curPos;					// текущая позиция на ленте
    State curState;				// текущее состояние машины
    vector<Rule> rules;			// вектор правил (программа)
    size_t rNum;				// количество правил
};

}

#endif //MT_H
