/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
#include "classes/NcursesGraphicLib.hpp"

Arcade::NcursesGraphicLib *main_instance;

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading ncurses library ...\n");
	main_instance = new Arcade::NcursesGraphicLib();
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Destroying ncurses library ...\n");
	delete main_instance;
}

extern "C" Arcade::NcursesGraphicLib *entryPoint()
{
 	return main_instance;
}


