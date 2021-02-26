#ifndef UTILS_H
#define UTILS_H
#include <ncurses.h>
bool can_go(int x, int y){
    int testch;
    /* return true if the space is okay to move into */

    testch = mvinch(y, x);
    if (testch == ' '){
        return true;
    } else {
        return false;
    }
}

bool can_go(int x, int y);
#endif
