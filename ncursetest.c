#include <ncurses.h>
#include <unistd.h>

int main() {

    initscr();
    noecho();
    curs_set(FALSE);

    sleep(2);

    endwin();
    return 0;
}
