#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define X_LIMIT 20
#define Y_LIMIT 20
#define TREASURE_COUNT 10

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

    srand(time(0));
    initscr();
    noecho();
    nodelay(stdscr,TRUE);
    curs_set(FALSE);
    timeout(0);

    char inChar;

    struct coord playerPos = {0,0};
    char exitFlag = 0;
    int score = 0;

    struct coord **treasureArray = (struct coord **)malloc(sizeof(struct coord *)*TREASURE_COUNT);

    for (int i = 0; i < TREASURE_COUNT; i++) {
        *(treasureArray + i) = NULL;
    }

    while(exitFlag == 0) {

        for (int i = 0; i < TREASURE_COUNT; i++) {
            if (*(treasureArray + i) == NULL) {
                *(treasureArray + i) = (struct coord *)malloc(sizeof(struct coord));
                (*(treasureArray + i))->x = rand()%X_LIMIT + 1; (*(treasureArray + i))->y = rand()%Y_LIMIT + 1;
            }
        }

        inChar = getch();

        switch(inChar) {

            case 'a': playerPos.x--; break;
            case 'd': playerPos.x++; break;
            case 's': playerPos.y++; break;
            case 'w': playerPos.y--; break;
            case 'c': exitFlag = 1; break;

        }

        flushinp();

        constrainPlayer(&playerPos);

        for (int i = 0; i < TREASURE_COUNT; i++) {
            if (*(treasureArray + i) != NULL &&
                playerPos.x == (*(treasureArray + i))->x &&
                playerPos.y == (*(treasureArray + i))->y)
            {
                free(*(treasureArray + i));
                *(treasureArray + i) = NULL;
                score++;
            }
        }

        generateBorder();

        move(playerPos.y, playerPos.x);
        printw("@");

        for (int i = 0; i < TREASURE_COUNT; i++) {
            if (*(treasureArray + i) != NULL) {
                move((*(treasureArray + i))->y, (*(treasureArray + i))->x);
                printw("X");
            }
        }

        move(0, X_LIMIT+3);
        printw("Score: %d",score);

        move(1, X_LIMIT+3);
        printw("Press the WASD keys to move!");
        move(2, X_LIMIT+3);
        printw("Press c to exit!");
        move(3, X_LIMIT+3);
        printw("Gather treasure by moving over X!");

        refresh();
        napms(25);
        clear();

    }

    for (int i = 0; i < 3; i++) {
        if (*(treasureArray + i) != NULL) {
            free(*(treasureArray + i));
        }
    }

    free(treasureArray);

    refresh();
    endwin();
    return 0;
}
