#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define X_LIMIT 10
#define Y_LIMIT 10

struct coord {
    int x;
    int y;
};

void generateBorder() {

    move(0,0);
    printw("0");

    for (int i = 1; i <= X_LIMIT; i++) {
        move(0,i);
        printw("-");
    }

    move(0,X_LIMIT+1);
    printw("0");

    for (int i = 1; i <= Y_LIMIT; i++) {
        move(i,X_LIMIT+1);
        printw("|");
    }

    move(Y_LIMIT+1,X_LIMIT+1);
    printw("0");

    for (int i = 1; i <= X_LIMIT; i++) {
        move(Y_LIMIT + 1,i);
        printw("-");
    }

    move(Y_LIMIT+1,0);
    printw("0");

    for (int i = 1; i <= Y_LIMIT; i++) {
        move(i,0);
        printw("|");
    }
}

struct coord generateTreasure() {

    struct coord treasurePos;

    srand(time(0));
    treasurePos.x = rand()%X_LIMIT + 1; treasurePos.y = rand()%Y_LIMIT + 1;

    return treasurePos;

}

void constrainPlayer(struct coord *pos) {

    if (pos->x > X_LIMIT) {
        pos->x = X_LIMIT;
    }
    if (pos->x < 1) {
        pos->x = 1;
    }

    if (pos->y > Y_LIMIT) {
        pos->y = Y_LIMIT;
    }
    if (pos->y < 1) {
        pos->y = 1;
    }
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

        constrainPlayer(&playerPos);

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
