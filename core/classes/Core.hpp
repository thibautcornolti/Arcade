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
		Core() = default;
		~Core() = default;

		void close();
		void run();
		bool init();
		void openGame(size_t);
		void swapLib(Arcade::Keys);
		void runGame(const std::string &);
		Arcade::IGraphicLib &getGraph();
		Arcade::IGameLib &getGame();
protected:
	private:
		bool _initGraphs();
		bool _initGames();

		std::vector<Arcade::IGraphicLib *> _graphs;
		std::vector<Arcade::IGameLib *> _games;
		std::vector<std::string> _gamesName;
		std::vector<std::shared_ptr<DLLoader>> _loaders;
		size_t _libGameIncrementer = 0;
		size_t _libGraphIncrementer = 0;
		bool _inMenu = true;
};
