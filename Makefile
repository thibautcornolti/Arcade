all:
	make re -C graphical/*/
	make re -C games/testgame/
	make re -C core
	mv core/program .
