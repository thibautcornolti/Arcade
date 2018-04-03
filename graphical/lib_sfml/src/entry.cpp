/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
#include "classes/SfmlGraphicLib.hpp"

Arcade::SfmlGraphicLib *main_instance;

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading sfml library ...\n");
	main_instance = new Arcade::SfmlGraphicLib();
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Destroying sfml library ...\n");
	delete main_instance;
}

extern "C" Arcade::SfmlGraphicLib *entryPoint()
{
 	return main_instance;
}


