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

int main() {

    initscr();
    noecho();
    curs_set(FALSE);
    timeout(0);

    char inChar;

    int x, y;
    x = 0;
    y = 0;

    while(1) {

        inChar = getch();

        switch(inChar) {

            case 'a': x--; break;
            case 'd': x++; break;
            case 's': y++; break;
            case 'w': y--; break;

        }

        move(y, x);
        printw("X: %d Y: %d", x, y);

        refresh();
        napms(50);
        clear();

        if (x < 0 || y < 0) {
            refresh();
            break;
        }

    }



    sleep(1);

    endwin();
    return 0;
}
