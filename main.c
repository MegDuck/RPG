#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//user headers
#include "entity.h"


struct _blocks {
    char entity;
    char block;
};

int hp;
int chp;
int monster_hp;
int max_monster_hp;

struct _blocks blocks  = {'*', 'O'};


void erase_title(){
    for (int x=10; x < COLS; x++){
        mvaddch(0, x, ' ');
    }
}



// base init
void init_game(){
    // Do not change monster_hp!
    monster_hp = 0;
    // But you can change hp and max_monster_hp
    hp = 10;
    chp = hp;
    max_monster_hp = 3;
    initscr();
    noecho();
    keypad(stdscr, true);
    cbreak();
    curs_set(0);
    for (int y = 0; y < LINES; y++) {
        mvhline(y, 0, ' ', COLS);
    }
    for (int x=0; x < COLS; x++){
        mvaddch(1, x, '-');
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

void attack_monster(){
    if (monster_hp == 0){
        monster_hp = rand()%3;
    } else {
        monster_hp -= 1;
        if (monster_hp <= 0){

        }
    }
}


int monster_check(int x, int y){
    int testch;
    for (int i=x-1; i<x+1; i++){
        for (int j=y-1; j<y+1; j++){
            testch = mvinch(j, i);
            if (testch == '*'){
                return 1;
            }
        }
    }
    return 0;
}


int main(){
    init_game();
    int y = 20;
    int x = 20;
    mvaddstr(y, x, "@");
    while(1){
        char *str = atoi(chp) + "/" + atoi(hp);
        mvaddstr(0, 2, str);
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
                attack_monster();
            } else {
                mvaddstr(0, 10, "Can't attack");
                signal(SIGALRM, erase_title);
                alarm(5);
            }
        }

        mvaddch(y, x, '@');
    }
    end_game();
}
