#include "fine.hpp"

fine::fine() {
    strcpy(nome,"INSERISCI IL TUO NOME:");
    punti=0;
    strcpy(end,"###   #   #   # #\n#     ##  #   #   #\n###   # # #   #   #\n#     #  ##   #   #\n###   #   #   # #\0");
};

//Gestisce l'inserimento del nome
void fine::drawnome() {
    sch.controllaDimensione(70,35);
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int w = 60;
    if (maxX < 64) w = maxX - 4;
    int h = 3;
    int startY;
    int startX = (maxX - w)/2;
    int nm=w-4;
    if (nm<1) nm=1;
    bool dist;
    dist=drawend();
    if (dist)startY = 15;
    else startY = 8;
    win3 = newwin(h, w, startY, startX);
    box(win3, 0, 0);
    mvwaddnstr(win3, 1, 2, nome, nm);
    keypad(win3,true);
    int a=0;
    int ch;
    nome[0]='\0';
    wmove(win3, 1, 2);
    wrefresh(win3);
    while((ch = wgetch(win3)) != '\n'||a<=3) {
        switch (ch) {
        case KEY_RESIZE:
            getmaxyx(stdscr, maxY, maxX);
            if (!sch.controllaDimensione(70,35)) {
                clear();
                refresh();
            }
            w = (maxX < 64) ? maxX - 4 : 60;
            startX = (maxX - w)/2;
            wresize(win3, h, w);
            dist=drawend();
            if (dist)startY = 15;
            else startY = 8;
                mvwin(win3, startY, startX);
            if (a>nm) {
                a=nm;
                nome[a]='\0';
            }
            break;
        case KEY_BACKSPACE:
        case 127:
            if(a>=1) {
                a--;
                nome[a]='\0';
            }
            break;
        default:
            if ((ch >= 48 && ch <= 57)||(ch>=65 && ch<=90)||(ch>=97 && ch<=122)) {
                nm=w-4;
                if(a<nm) {
                    nome[a++]=ch;
                    nome[a] = '\0';
                }
            }
            break;
    }
        nm=w-4;
        if (nm<1) nm=1;
            werase(win3);
            box(win3, 0, 0);
            mvwaddnstr(win3, 1, 2, nome, nm);
            wmove(win3, 1, 2 + a);
            wrefresh(win3);
        }
    addclass("Classifica.txt");
    clear();
    refresh();
    getch();
    endwin();
};

void fine::addpunteggio(int t) {
    punti=t;
}

//Scrive la scritta END
bool fine::drawend() {
    int x,y;
    getmaxyx(stdscr,y,x);
    if (y > 30 && x > 80) {
        int w=21;
        int h=7;
        win4 = newwin(h, w, 3, (x - w) / 2);
        wattron(win4, COLOR_PAIR(1));
        mvwprintw(win4, 2, 0, "%s", end);
        wattroff(win4, COLOR_PAIR(1));
        wrefresh(win4);
        return true;
    } else {
        win4 = newwin(3, 15, 2, (x - 12) / 2 - 2);
        wattron(win4, A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
        mvwprintw(win4, 1, 6, "END");
        box(win4, 0, 0);
        wattroff(win4, A_BOLD | COLOR_PAIR(1) | A_UNDERLINE);
        wrefresh(win4);
        return false;
    }
};

//Conta il numero di righe del file
int fine::contaRighe(char t[]) {
    ifstream inputFile;
    inputFile.open(t);
    if (!inputFile) return -1;
    int righe = 0;
    char ch;
    bool vuoto = true;
    while (!inputFile.eof()) {
        inputFile.get(ch);
        if (inputFile.eof()) break;
        vuoto = false;
        if (ch == '\n') {
            righe++;
            vuoto = true;
        }
    }
    if (vuoto == false) righe++;
    inputFile.close();
    return righe;
}

//Aggiunge il giocatore e il suo punteggio alla classifica
void fine::addclass(char t[]) {
    ifstream inputFile;
    inputFile.open(t);
    int n=0;
    int p=contaRighe(t);
    if (p==-1) return;
    while (n<p) {
        inputFile>>classifica[n].nom>>classifica[n].punt;
        n++;
    }
    inputFile.close();
    bool c=false;
    int tot=p;
    if (p == 0) {
        classifica[0].punt = punti;
        strcpy(classifica[0].nom, nome);
    }
    while (p>0 && c==false) {
        if (punti<=classifica[p-1].punt) {
            classifica[p].punt=punti;
            strcpy(classifica[p].nom,nome);
            c=true;
        }else {
            classifica[p].punt=classifica[p-1].punt;
            strcpy(classifica[p].nom,classifica[p-1].nom);
            if (p==1) {
                classifica[p-1].punt=punti;
                strcpy(classifica[p-1].nom,nome);
            }
        }
        p--;
    }
    ofstream outputFile;
    outputFile.open(t);
    for (int i=0;i<=tot;i++) {
        outputFile<<classifica[i].nom<<" "<<classifica[i].punt<<"\n";
    }
    outputFile.close();
};
