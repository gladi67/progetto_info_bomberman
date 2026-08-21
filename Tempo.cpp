#include "Tempo.hpp"

tempo::tempo() {
    larghezza = 10;
    altezza = 3;
    getmaxyx(stdscr, maxy, maxx);
    maxx -= 15;
    win1 = NULL;
}
void tempo:: avvia(int t) {
    durata = t;
    tempo_rimasto = t;
    tempo_inizio = time(NULL);
}

void tempo:: finestra() {
    getmaxyx(stdscr, maxy, maxx);
    maxx-=15;
    int y = 2;
    int x = maxx - larghezza - 5;
    if (x < 0) x = 0;
    if (win1 == NULL) {
        win1 = newwin(altezza, larghezza, y, x);
    }else mvwin(win1, y, x);
    box(win1, 0, 0);
    scrivitempo();
}

void tempo:: scrivitempo() {
    if (win1 == NULL) return;
    mvwprintw(win1, 1, 2, "%06d", tempo_rimasto);
    wrefresh(win1);
}

void tempo:: diminuiscitempo() {
    if (win1 == NULL) return;
    time_t tempo_attuale = time(NULL);
    tempo_rimasto = durata - (tempo_attuale - tempo_inizio);
    scrivitempo();
}

void tempo::addpausa(int t) {
    tempo_inizio += t;
}
