/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include "classes/LibAnalyzer.hpp"
#include "classes/DLLoader.hpp"
#include "classes/Core.hpp"
#include "shared_header/IGraphicLib.hpp"

Core *coreGetter(Core *set)
{
	static Core *core = nullptr;

	if (set)
		core = set;
	return core;
}

void sighandler(int)
{
	coreGetter(nullptr)->close();
}

int main()
{
	Core core;

	coreGetter(&core);
	signal(SIGINT, sighandler);
	if (core.init()) {
		core.run();
		core.stop();
	}
	return (0);
}

