/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <signal.h>
#include <memory>
#include "classes/NcursesGraphicLib.hpp"

Arcade::NcursesGraphicLib *main_instance;

void sig_handler(int sig)
{
	printf("AH\n");
	main_instance->closeRendering();
	main_instance->stopRenderer();
}

__attribute__((constructor))
void cons()
{
	printf("[libfoo] Loading ncurses library ...\n");
	signal(SIGINT, sig_handler);
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


