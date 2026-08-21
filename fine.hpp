#ifndef BOMBERMAN_FINE_H
#define BOMBERMAN_FINE_H
using namespace std;
#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <cstring>
#include "Schermo.hpp"
struct cl{
    char nom[100];
    int punt;
};
class fine {
protected:
    WINDOW*win3;
    WINDOW*win4;
    char nome[100];
    int punti;
    char end[100];
    cl classifica[200];
    Schermo sch;
public:
    fine();
    void drawnome();
    bool drawend();
    int contaRighe(char t[]);
    void addclass(char t[]);
    void addpunteggio(int t);
};
#endif