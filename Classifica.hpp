#ifndef BOMBERMAN_CLASSIFICA_H
#define BOMBERMAN_CLASSIFICA_H
using namespace std;
#include <iostream>
#include"Schermo.hpp"
#include <ncurses.h>
#include <cstring>
#include <fstream>

class Classifica {
protected:
    int contaRighe(char t[]);
    char numpunti[60];
    Schermo sch;
public:
    Classifica();
    void Npunti();
    void mostra(int PUN);
};
#endif
