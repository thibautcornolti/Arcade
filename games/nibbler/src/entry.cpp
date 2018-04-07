/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
#include "classes/Nibbler.hpp"

Arcade::Nibbler *main_instance;

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading nibbler game ...\n");
	main_instance = new Arcade::Nibbler();
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Destroying nibbler game ...\n");
	delete main_instance;
}

extern "C" Arcade::Nibbler *entryPoint()
{
 	return main_instance;
}


