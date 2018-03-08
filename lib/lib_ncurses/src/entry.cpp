/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <stdio.h>
#include <memory>
//#include "classes/GraphicLib.hpp"

//Arcade::GraphicLib *main_instance;

__attribute__((constructor))
void cons()
{
//	main_instance = new Arcade::GraphicLib();
	printf("[libfoo] Loading foo library ...\n");
}

__attribute__((destructor))
void dest()
{
	printf("[libfoo] Loading foo library ...\n");
}

// extern "C" Arcade::IGraphicLib *entryPoint()
// {
// 	printf("[libfoo] Another entry point !\n");
// 	return main_instance;
// }


