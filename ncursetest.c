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

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    for (int i = 1; i <= 4; i++) {

        attrset(COLOR_PAIR(i));
        helloWorld();
        clear();
        refresh();
        attroff(COLOR_PAIR(i));

    }

    move(30, 10);
    printw("%d", 100);
    refresh();

    sleep(2);

    endwin();
    return 0;
}
