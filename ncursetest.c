#include <ncurses.h>
#include <unistd.h>

struct coord {
    int x;
    int y;
};

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

void wrapAround(struct coord *pos) {
    if (pos->y >= LINES) {
        pos->y = pos->y % LINES;
    } else if (pos->y < 0) {
        pos->y = LINES + (pos->y % LINES);
    }

    int xLimit = COLS - 15;

    if (pos->x >= xLimit) {
        pos->x = pos->x % xLimit;
    } else if (pos->x < 0) {
        pos->x = xLimit + (pos->x % xLimit);
    }
}

int main() {

    initscr();
    noecho();
    curs_set(FALSE);
    timeout(0);

    char inChar;

    struct coord playerPos = {0,0};
    int exitFlag = 0;

    while(exitFlag == 0) {

        inChar = getch();

        switch(inChar) {

            case 'a': playerPos.x--; break;
            case 'd': playerPos.x++; break;
            case 's': playerPos.y++; break;
            case 'w': playerPos.y--; break;
            case 27: exitFlag = 1; break;

        }

        wrapAround(&playerPos);

        move(playerPos.y, playerPos.x);
        printw("X: %d Y: %d", playerPos.x, playerPos.y);

        refresh();
        napms(25);
        clear();

    }


    refresh();
    endwin();
    return 0;
}
