# RPG
 Little ascii RPG in terminal.

## How to build?

Install libncursesw5 for normal work.

Debian/Ubuntu-based systems: apt install libncursesw5-dev libncurses5-dev 


Fedora 21 and older, RHEL, CentOS... - sudo yum install ncurses-devel

Fedora 22+ - sudo dnf install ncurses-devel

Arch-based: sudo pacman -S ncurses



gcc entity.c entity.h main.c -lncurses -o game

And you get an executable game!


Tested on Android/PC(PeppermintOS)
