#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

//for messages delete
#include <unistd.h>
#include <signal.h>

//for correct colors
#include <locale.h>

//user headers
#include "entity.h"


struct _blocks {
    char entity;
    char block;
};

int hp;
int chp;
int monster_hp;
int cmhp;
int max_monster_hp;

struct _blocks blocks  = {'*', 'O'};


void erase_title(){
    for (int x=10; x < COLS; x++){
        mvaddch(0, x, ' ');
    }
}

 /* itoa:  convert n to characters in s */

/* The Itoa code is in the puiblic domain */
char* itoa(int value, char* str, int radix) {
    static char dig[] =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz";
    int n = 0, neg = 0;
    unsigned int v;
    char* p, *q;
    char c;

    if (radix == 10 && value < 0) {
        value = -value;
        neg = 1;
    }
    v = value;
    do {
        str[n++] = dig[v%radix];
        v /= radix;
    } while (v);
    if (neg)
        str[n++] = '-';
    str[n] = '\0';
    for (p = str, q = p + n/2; p != q; ++p, --q)
        c = *p, *p = *q, *q = c;
    return str;
}


// base init
void init_game(){
    // Do not change monster_hp!
    monster_hp = 1;
    cmhp = monster_hp;
    // But you can change hp and max_monster_hp
    hp = 10;
    chp = hp;
    max_monster_hp = 4;

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    nonl();
    keypad(stdscr, true);
    cbreak();
    curs_set(0);
    for (int y = 0; y < LINES; y++) {
        mvhline(y, 0, ' ', COLS);
    }
    for (int x=0; x < COLS; x++){
        mvaddch(1, x, '-');
    }
    if(has_colors() == true){
        start_color();
    }

}

// end
void end_game(){
    echo();
    nocbreak();
    endwin();
}



int can_go(int x, int y){
    int testch;
    /* return true if the space is okay to move into */

    testch = mvinch(y, x);
    return ((testch == ' '));
}

char *input(){
    int ch = getch();
    if (ch == KEY_LEFT){
        return "left";
    } else if (ch == KEY_RIGHT){
        return "right";
    } else if (ch == KEY_UP){
        return "up";
    } else if (ch == KEY_DOWN){
        return "down";
    } else if (ch == KEY_HOME){
        return "home";
    } else if (ch == 'a'){
        return "attack";
    }
}

void attack_monster(int x, int y){
    if (cmhp <= 0){
        while (cmhp == 0){
        	monster_hp = rand()%max_monster_hp;
        	cmhp = monster_hp;
	}
        erase_title();
        mvaddstr(0, 10, "Killed");
	signal(SIGALRM, erase_title);
	alarm(2);
        int monster;
        for (int i=x-1; i<x+1; i++){
            for (int j=y-1; j<y+1; j++){
                monster = mvinch(j, i);
                if (monster == '*'){
                    mvaddch(j, i, ' ');
                }
            }
        }
    } else {
        cmhp -= 1;
    }
}


int monster_check(int x, int y){
    int testch;
    for (int i=x-1; i<x+1; i++){
        for (int j=y-1; j<y+1; j++){
            testch = mvinch(j, i);
            mvaddch(5,5,testch);
            if (testch == '*'){
                return 1;
            }
        }
    }
    return 0;
}


int main(void){
    init_game();
    int y = 20;
    int x = 20;
    mvaddstr(y, x, "@");
    while(1){
        mvwprintw(stdscr, 0, 2, "%d/%d", chp, hp);
        char *action = input();
        mvaddch(y, x, ' ');
        new_ent(10, 10);
        if (action == "left"){
            if ((x > 0) && can_go(y, x - 1)) {
                x = x - 1;
            }
        } else if (action == "right") {
            if ((x < COLS - 1) && can_go(y, x + 1)) {
                x = x + 1;
            }
        } else if (action == "up"){
            if ((y > 0) && can_go(y - 1, x)) {
                y = y - 1;
            }
        } else if (action == "down"){
            if ((y < LINES - 1) && can_go(y + 1, x)) {
                y = y + 1;
            }
        } else if (action == "attack"){
            if (monster_check(x, y) == 1){
                erase_title();
                attack_monster(x, y);
            } else {
                init_pair(1, COLOR_BLACK, COLOR_YELLOW);
                attron(COLOR_PAIR(1));
                mvaddstr(0, 10, "Can't attack");
                attroff(COLOR_PAIR(1));
                signal(SIGALRM, erase_title);
                alarm(5);
            }
        }
	if (monster_check(x, y) == 1){
		mvprintw(0, 30, "M:%d/%d", cmhp, monster_hp);
	}
        mvaddch(y, x, '@');
    }
    end_game();
    return 0;
}
