/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
#include "classes/Snake.hpp"

Arcade::Snake *main_instance;

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading snake game ...\n");
	main_instance = new Arcade::Snake();
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Destroying snake game ...\n");
	delete main_instance;
}

extern "C" Arcade::Snake *entryPoint()
{
 	return main_instance;
}


