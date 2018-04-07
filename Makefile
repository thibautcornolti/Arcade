all:
	make -C lib/sdl/
	make re -C lib/ncurses/
	make -C lib/sfml/
	make -C games/testgame/
	make -C games/snake/
	make -C games/pacman/
	make -C core/
	cp core/arcade .

re:
	make re -C lib/sdl/
	make re -C lib/ncurses/
	make re -C lib/sfml/
	make re -C games/testgame/
	make re -C games/snake/
	make re -C games/pacman/
	make re -C core/
	cp core/arcade .

clean:
	make clean -C lib/sdl/
	make clean -C lib/ncurses/
	make clean -C lib/sfml/
	make clean -C games/testgame/
	make clean -C games/snake/
	make clean -C games/pacman/
	make clean -C core/

fclean:
	rm core/arcade
	rm arcade
	make fclean -C lib/sdl/
	make fclean -C lib/ncurses/
	make fclean -C lib/sfml/
	make fclean -C games/testgame/
	make fclean -C games/snake/
	make fclean -C games/pacman/
	make fclean -C core/
