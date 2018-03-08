all:
	make re -C lib/lib_ncurses
	#make -C games/*
	make re -C core
	mv core/program .
