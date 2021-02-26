#include <ncurses.h>
#include <stdlib.h>



void new_ent(int x, int y){
    mvaddstr(y, x, "*");
}

void generate_ents(int count){
    int counter =0;
    while(counter!=count){
        int y = rand()%COLS;
        int x = rand()%LINES;
        if (can_go(x, y)){
            new_ent(x, y);
            counter++;
        }
    }
}
