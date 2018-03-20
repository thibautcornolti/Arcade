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

class Core {
	public:
		Core();
		~Core();

		void close();
		void run();
		void stop();
		bool init();
		void swapLib(Arcade::Keys);
	protected:
	private:
		Arcade::IGraphicLib &_getLib();

		std::vector<Arcade::IGraphicLib *> _libs;
		std::vector<std::shared_ptr<DLLoader>> _loaders;
		size_t _libIncrementer = 0;
};