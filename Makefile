ncursetest: ncursetest.c
	gcc nctreasurehunt.c -lncurses -o nctreasurehunt

ncursetest_debug: ncursetest.c
	gcc nctreasurehunt.c -lncurses -o nctreasurehunt -g

.PHONY: clean

clean:
	-@rm -f test
	-@rm -f nctreasurehunt
	-@rf -f *.o
