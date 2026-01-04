ncursetest: ncursetest.c
	gcc ncursetest.c -lncurses -o ncursetest

ncursetest_debug: ncursetest.c
	gcc ncursetest.c -lncurses -o ncursetest -g

test: ncursetest.c
	gcc test.c -o test

.PHONY: clean

clean:
	-@rm -f test
	-@rm -f ncursetest
	-@rf -f *.o
