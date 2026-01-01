#include <ncurses.h>
#include <unistd.h>

void helloWorld() {

    for (int i = 0; i < 10; i++) {

        move(10 + 2*i,10);
        addstr("Hello World!");
        move(11 + 2*i,10);
        addstr("How are you doing?");
        refresh();
        napms(120);

    }

}

void wrapAround(int *x, int *y) {
    if (*y >= LINES) {
        *y = *y % LINES;
    } else if (*y < 0) {
        *y = LINES + (*y % LINES);
    }

    int xLimit = COLS - 15;

    if (*x >= xLimit) {
        *x = *x % xLimit;
    } else if (*x < 0) {
        *x = xLimit + (*x % xLimit);
    }
}

int main() {

    initscr();
    noecho();
    curs_set(FALSE);
    timeout(0);

    char inChar;

    int x, y, exitFlag;
    x = 0;
    y = 0;
    exitFlag = 0;

    while(exitFlag == 0) {

        inChar = getch();

        switch(inChar) {

            case 'a': x--; break;
            case 'd': x++; break;
            case 's': y++; break;
            case 'w': y--; break;
            case 'c': exitFlag = 1; break;

        }

        wrapAround(&x,&y);

        move(y, x);
        printw("X: %d Y: %d", x, y);

        refresh();
        napms(10);
        clear();

    }


    refresh();
    sleep(1);

    endwin();
    return 0;
}
