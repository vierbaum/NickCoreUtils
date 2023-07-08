#include <printf.h>
#include <string.h>
#include "frac.h"
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct {
    int pos[2];
    char* text;
    int isHighlighted;
} Button;

int main(int argc, char* argv[]) {
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);


    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "This text is red on black");
    attroff(COLOR_PAIR(1));
    refresh();
    getch();
    endwin();

    char ch;
    char buff[256];

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);




    Frac f1 = genFrac(1, 2);
    Frac f2 = genFrac(18, 3);
    char* s = (char*) malloc(255);

    Frac f3 = f1 * f2;
    register_printf_function('K', print_frac, print_frac_arginfo);
    printf("%K\n", &f3);

    return 0;
}