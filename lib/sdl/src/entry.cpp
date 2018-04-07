/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
#include "classes/SdlGraphicLib.hpp"

Arcade::SdlGraphicLib *main_instance;

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading sdl library ...\n");
	main_instance = new Arcade::SdlGraphicLib();
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Destroying sdl library ...\n");
	delete main_instance;
}

extern "C" Arcade::SdlGraphicLib *entryPoint()
{
 	return main_instance;
}


