/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
#include "classes/Pacman.hpp"

Arcade::Pacman *main_instance;

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading pacman game ...\n");
	main_instance = new Arcade::Pacman();
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Destroying pacman game ...\n");
	delete main_instance;
}

extern "C" Arcade::Pacman *entryPoint()
{
 	return main_instance;
}


