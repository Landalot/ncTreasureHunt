nctreasurehunt: nctreasurehunt.c
	gcc nctreasurehunt.c -lncurses -o nctreasurehunt

nctreasurehunt_debug: nctreasurehunt.c
	gcc nctreasurehunt.c -lncurses -o nctreasurehunt -g

.PHONY: clean

clean:
	-@rm -f test
	-@rm -f nctreasurehunt
	-@rf -f *.o
