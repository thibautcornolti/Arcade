/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "LibAnalyzer.hpp"
#include "DLLoader.hpp"
#include "../shared_header/IGraphicLib.hpp"
#include "../shared_header/IGameLib.hpp"

class Core {
	public:
		Core();
		~Core();

		void close();
		void run();
		void stop();
		bool init();
		void swapLib(Arcade::Keys);
		Arcade::IGraphicLib &_getGraph();

protected:
	private:
		Arcade::IGameLib &_getGame();
		bool _initGraphs();
		bool _initGames();

		std::vector<Arcade::IGraphicLib *> _graphs;
		std::vector<Arcade::IGameLib *> _games;
		std::vector<std::shared_ptr<DLLoader>> _loaders;
		size_t _libGameIncrementer = 0;
		size_t _libGraphIncrementer = 0;
};
