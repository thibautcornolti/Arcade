/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
#include "classes/TestGameLib.hpp"

Arcade::TestGameLib *main_instance;

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading test game ...\n");
	main_instance = new Arcade::TestGameLib();
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Destroying test game ...\n");
	delete main_instance;
}

extern "C" Arcade::TestGameLib *entryPoint()
{
 	return main_instance;
}


