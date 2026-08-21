#ifndef BOMBERMAN_GAMEMASTER_H
#define BOMBERMAN_GAMEMASTER_H
using namespace std;
#include "Classifica.hpp"
#include "fine.hpp"
#include "Menu.hpp"
#include "Punti.hpp"
#include "Tempo.hpp"
#include "Schermo.hpp"
#include <ctime>

enum StatoGioco {
    STATO_MENU, STATO_PARTITA, STATO_FINE, STATO_ESCI, STATO_CLASSIFICA
};

class Gamemaster {
protected:
    StatoGioco stato;
    Menu menu;
    Classifica classifica;
    fine Fine;
    punti Punti;
    tempo Tempo;
    Schermo schermo;
    int oldH;
    int oldW;
    void responsive();
public:
    Gamemaster();
    void startmenu();
    void startclassifica();
    void startfine();
    void closeapp();
    void startpartita();
    void run();
};
#endif
