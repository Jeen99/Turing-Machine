#include "MT.h"
#define RESERVE_LEFT 50         //резерв для ленты слева

namespace Turing {

    MT::MT(void)
    {
        curPos = RESERVE_LEFT;
        rNum = 0;
    }

    void MT::setState(string state)
    {
        curState.q = state;
    }

    void MT::setMem(string mem)
    {
        curPos = RESERVE_LEFT;
        this->mem.clear();
        this->mem.resize(curPos, ' ');   //для добавления слева свободного места
        this->mem += mem;
        curState.sym = this->mem[curPos];
    }

    char MT::getSym() const
    {
        return mem[curPos];
    }

    int MT::getPosition() const
    {
        return curPos;
    }

    string MT::getState() const
    {
        return curState.q;
    }

    string MT::getMem() const
    {
        return mem;
    }

    void MT::addRule(string rule)
    {
        rules.push_back(*new Rule);                     //выделяем место под новое правило
        rules[rNum].curQ.assign(rule, 0, width);		//получение тек. состояния
        rules[rNum].curSym = rule[width];				//получение тек. символа
        size_t pos = rule.find("->") + 2;
        rules[rNum].nextQ.assign(rule, pos, width);		//получение след. состояния
        rules[rNum].nextSym = rule[rule.length() - 2];	//получение след. символа
        rules[rNum].cmd = rule[rule.length() - 1];		//получение направления
        rNum++;
    }

    void MT::loadRule(string path)
    {
        ifstream file(path);

        if (file.fail())                //если файл с правилами не найден
            exit(-1);                    //выходим из программы

        rules.clear();
        rNum = rules.size();

        string rule;

        while (!file.eof())             //проверка на конец файла
        {
            std::getline(file,rule);
            if (rule.size() == 9 && rule[0] != '#')
                addRule(rule);
        }
        file.close();
    }

    void MT::process(int i)
    {
        if (rules[i].cmd == 'L')
            curPos += L;
        else if (rules[i].cmd == 'R')
            curPos += R;
        curState.q = rules[i].nextQ;

        if (curPos < 0)
            return;

        if (curPos >= mem.length())
            mem.resize(mem.size() + 1, ' ');
        curState.sym = mem[curPos];
    }

    void MT::step()
    {
        for (int i = 0; i < rNum; i++)
        {
            if (curState.q == rules[i].curQ && curState.sym == rules[i].curSym)
            {
                mem[curPos] = rules[i].nextSym;
                process(i);
                break;
            }
        }
    }

}
