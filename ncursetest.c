#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define X_LIMIT 50
#define Y_LIMIT 20

struct coord {
    int x;
    int y;
};

void wrapAround(struct coord *pos) {

    int xLimit = 30;
    int yLimit = 20;

    if (pos->y >= Y_LIMIT) {
        pos->y = pos->y % Y_LIMIT;
    } else if (pos->y < 0) {
        pos->y = Y_LIMIT + (pos->y % Y_LIMIT);
    }

    if (pos->x >= X_LIMIT) {
        pos->x = pos->x % X_LIMIT;
    } else if (pos->x < 0) {
        pos->x = X_LIMIT + (pos->x % X_LIMIT);
    }
}

void generateBorder() {
    for (int i = 0; i <= Y_LIMIT; i++) {
        move(i,X_LIMIT);
        printw("|");
    }

    for (int i = 0; i < X_LIMIT; i++) {
        move(Y_LIMIT,i);
        printw("0");
    }
}

struct coord generateTreasure() {

    struct coord treasurePos;

    srand(time(0));
    treasurePos.x = rand(); treasurePos.y = rand();

    wrapAround(&treasurePos);

    return treasurePos;

}

int main() {

    initscr();
    noecho();
    curs_set(FALSE);
    timeout(0);

    char inChar;

    struct coord playerPos = {0,0};
    struct coord treasurePos;
    char exitFlag = 0;
    char treasureFlag = 0;
    int score = 0;

    while(exitFlag == 0) {

        if (treasureFlag == 0) {
            treasurePos = generateTreasure();
            treasureFlag = 1;
        }

        inChar = getch();

        switch(inChar) {

            case 'a': playerPos.x--; break;
            case 'd': playerPos.x++; break;
            case 's': playerPos.y++; break;
            case 'w': playerPos.y--; break;
            case 27: exitFlag = 1; break;

        }

        wrapAround(&playerPos);

        if (treasureFlag == 1 && playerPos.x == treasurePos.x && playerPos.y == treasurePos.y) {
            treasureFlag = 0;
            score++;
        }

        generateBorder();

        move(playerPos.y, playerPos.x);
        printw("@");

        if (treasureFlag == 1) {
            move(treasurePos.y, treasurePos.x);
            printw("X");
        }

        move(0, COLS - 10);
        printw("Score: %d",score);

        refresh();
        napms(25);
        clear();

    }


    refresh();
    endwin();
    return 0;
}
