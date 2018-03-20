all:
	make re -C graphical/lib_ncurses
	#make -C games/*
	make re -C core
	mv core/program .
