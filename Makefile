all:
	make re -C graphical/lib_ncurses/
	make -C graphical/lib_sfml/
	make -C games/testgame/
	make -C games/snake/
	make -C games/pacman/
	make -C core/
	cp core/arcade .

re:
	make re -C graphical/lib_ncurses/
	make re -C graphical/lib_sfml/
	make re -C games/testgame/
	make re -C games/snake/
	make re -C games/pacman/
	make re -C core/
	cp core/arcade .

clean:
	make clean -C graphical/lib_ncurses/
	make clean -C graphical/lib_sfml/
	make clean -C games/testgame/
	make clean -C games/snake/
	make clean -C games/pacman/
	make clean -C core/

fclean:
	rm core/arcade
	make fclean -C graphical/lib_ncurses/
	make fclean -C graphical/lib_sfml/
	make fclean -C games/testgame/
	make fclean -C games/snake/
	make fclean -C games/pacman/
	make fclean -C core/
