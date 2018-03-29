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
#include "menu/Menu.hpp"
#include "../shared_header/IGraphicLib.hpp"

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

void game(Core &core)
{
	Arcade::Keys key = Arcade::Keys::NONE;
	Menu menu(core, 50, 50);

	while (core._getGraph().isOpen()) {
		core._getGraph().pollEvents();
		key = core._getGraph().getLastEvent();
		core._getGraph().clearEvents();
		if (key != Arcade::Keys::NONE) {
			core.swapLib(key);
			if (key == Arcade::Keys::ESC) {
				core.close();
				break ;
			}
		}
		menu.run();
	}
}

int main()
{
	Core core;

	coreGetter(&core);
	signal(SIGINT, sighandler);
	if (core.init()) {
		core.run();
		game(core);
		core.stop();
	}
	return (0);
}

