all:
	make -C lib/sdl/
	make -C lib/ncurses/
	make -C lib/sfml/
	make -C games/testgame/
	make -C games/nibbler/
	make -C games/pacman/
	make -C core/
	mv core/arcade .

core:
	make -C core/
	mv core/arcade .

games:
	make -C games/testgame/
	make -C games/nibbler/
	make -C games/pacman/

graphicals:
	make -C lib/sdl/
	make -C lib/ncurses/
	make -C lib/sfml/

re:
	make re -C lib/sdl/
	make re -C lib/ncurses/
	make re -C lib/sfml/
	make re -C games/testgame/
	make re -C games/nibbler/
	make re -C games/pacman/
	make re -C core/
	mv core/arcade .

clean:
	make clean -C lib/sdl/
	make clean -C lib/ncurses/
	make clean -C lib/sfml/
	make clean -C games/testgame/
	make clean -C games/nibbler/
	make clean -C games/pacman/
	make clean -C core/

fclean:
	rm -rf arcade
	rm -rf lib/*.so
	rm -rf games/*.so
	make fclean -C lib/sdl/
	make fclean -C lib/ncurses/
	make fclean -C lib/sfml/
	make fclean -C games/testgame/
	make fclean -C games/nibbler/
	make fclean -C games/pacman/
	make fclean -C core/
