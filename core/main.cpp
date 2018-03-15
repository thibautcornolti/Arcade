/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "classes/LibAnalyzer.hpp"
#include "classes/DLLoader.hpp"
#include "shared_header/IGraphicLib.hpp"

int main()
{
	LibAnalyzer l;
	DLLoader dl(LIB_FOLDER"/" + l.getLibs()[0]);

	if (dl.isError()) {
		std::cout << dl.getError() << std::endl;
		return 1;
	}
	auto o = dl.getInstance<Arcade::IGraphicLib>();
	if (dl.isError()) {
		std::cout << dl.getError() << std::endl;
		return 2;
	}
	std::cout << o->isOpen() << std::endl;
	
	return (0);
}

