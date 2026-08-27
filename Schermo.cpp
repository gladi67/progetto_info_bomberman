#include "Schermo.hpp"

bool Schermo::controllaDimensione(int MIN_X, int MIN_Y) {
    int curY, curX;
    getmaxyx(stdscr, curY, curX);
    if (curY >= MIN_Y && curX >= MIN_X) {
        return false;
    }
    werase(stdscr);
    box(stdscr, 0, 0);
    mvwprintw(stdscr, 2, 2, "ATTENZIONE: Finestra troppo piccola!");
    mvwprintw(stdscr, 3, 2, "Allarga il terminale per continuare...");
    refresh();
    while (curY < MIN_Y || curX < MIN_X) {
        int ch = getch();
        if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, curY, curX);
            werase(stdscr);
            box(stdscr, 0, 0);
            mvwprintw(stdscr, 2, 2, "ATTENZIONE: Finestra troppo piccola!");
            mvwprintw(stdscr, 3, 2, "Allarga il terminale per continuare...");
            refresh();
        }
    }
    werase(stdscr);
    refresh();
    return true;
}