ncursetest: ncursetest.c
	gcc nctreasurehunt.c -lncurses -o nctreasurehunt

ncursetest_debug: ncursetest.c
	gcc nctreasurehunt.c -lncurses -o nctreasurehunt -g

test: test.c
	gcc test.c -o test

.PHONY: clean

clean:
	-@rm -f test
	-@rm -f nctreasurehunt
	-@rf -f *.o
