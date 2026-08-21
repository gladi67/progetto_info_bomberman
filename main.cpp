#include <ncurses.h>
#include "Gamemaster.hpp"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    Gamemaster game;
    game.run();
    endwin();
    return 0;
}