#include "Gamemaster.hpp"

Gamemaster::Gamemaster() {
    stato=STATO_MENU;
    oldH=0;
    oldW=0;
}

void Gamemaster::responsive() {
    int h, w;
    getmaxyx(stdscr, h, w);
    if (h != oldH || w != oldW) {
        time_t ora_inizio_blocco = time(NULL);
        if (!schermo.controllaDimensione(40,20)) {
            werase(stdscr);
            touchwin(stdscr);
            refresh();
        }else {
            int secondi_di_pausa = time(NULL) - ora_inizio_blocco;
            if (stato==STATO_PARTITA) {
                Tempo.addpausa(secondi_di_pausa);
            }
        }
        oldH = h;
        oldW = w;
        if (stato == STATO_MENU) menu.drawMenu();
        else if (stato == STATO_PARTITA) {
            Tempo.finestra();
            Punti.finestra();
        }
    }
}
void Gamemaster::startmenu() {
    schermo.controllaDimensione(40,20);
    nodelay(stdscr, FALSE);
    menu.setTitle("####      ##     #     #  ####   ####  ####   #     #    #    #     #\n#   #   #    #   ##   ##  #   #  #     #   #  ##   ##   # #   ##    #\n#   #  #      #  # # # #  #   #  #     #   #  # # # #  #   #  # #   #\n####   #      #  #  #  #  ####   ####  ####   #  #  #  #####  #  #  #\n#   #  #      #  #     #  #   #  #     #  #   #     #  #   #  #   # #\n#   #   #    #   #     #  #   #  #     #   #  #     #  #   #  #    ##\n####      ##     #     #  ####   ####  #   #  #     #  #   #  #     #\n");
    menu.drawMenu();
    while (stato==STATO_MENU) {
        responsive();
        int ch = getch();
        if (ch==KEY_MOUSE){
            MEVENT event;
            if (getmouse(&event) == OK) {
                int butt=menu.controllaClick(event);
                if (butt==0) {
                    stato=STATO_PARTITA;
                }else if (butt==1) {
                    stato=STATO_CLASSIFICA;
                }else if (butt==2) {
                    stato=STATO_ESCI;
                }
            }
        }
    }
}

void Gamemaster::startclassifica() {
    nodelay(stdscr, FALSE);
    classifica.Npunti();
    stato=STATO_MENU;
}

void Gamemaster::startfine() {
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    Fine.addpunteggio(Punti.puntif());
    Fine.drawend();
    Fine.drawnome();
    stato=STATO_ESCI;
}

void Gamemaster::closeapp() {
    clear();
    refresh();
    getch();
    endwin();
}

void Gamemaster::startpartita() {
    keypad(stdscr, TRUE);
    timeout(100);
    Tempo.avvia(60);
    Punti.azzera();
    werase(stdscr);
    refresh();
    Tempo.finestra();
    Punti.finestra();
    while (stato==STATO_PARTITA) {
        responsive();
        int t=getch();
        if (t!=ERR) {
            Punti.modificapunti(t);
            if (Punti.puntif()>=1000) {
                stato=STATO_FINE;
            }
        }
        Tempo.diminuiscitempo();
        if (Tempo.tempo_rimasto<=0) {
            stato=STATO_FINE;
        }
    }
    werase(stdscr);
    touchwin(stdscr);
    refresh();
}

void Gamemaster::run() {
    getmaxyx(stdscr, oldH, oldW);
    while (stato!=STATO_ESCI) {
        switch (stato) {
            case STATO_MENU:
                startmenu();
                break;
            case STATO_PARTITA:
                startpartita();
                break;
            case STATO_CLASSIFICA:
                startclassifica();
                break;
            case STATO_FINE:
                startfine();
                break;
            case STATO_ESCI:
                break;
        }
    }
    closeapp();
}