all:
	make re -C graphical/lib_ncurses/
	make re -C graphical/lib_sfml/
	make re -C games/testgame/
	make re -C core
	mv core/arcade .
