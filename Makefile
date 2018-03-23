all:
	make re -C graphical/*/
	make re -C games/*/
	make re -C core
	mv core/program .
