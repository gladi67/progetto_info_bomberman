#ifndef BOMBERMAN_SCHERMO_H
#define BOMBERMAN_SCHERMO_H
#include <ncurses.h>

class Schermo {
public:
    const int MIN_Y = 20;
    const int MIN_X = 40;
    bool controllaDimensione();
};
#endif
