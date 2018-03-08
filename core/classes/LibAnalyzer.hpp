/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <vector>
#include <string>
#include <dirent.h>
#include "../config.hpp"

class LibAnalyzer {
	public:
		LibAnalyzer();
		~LibAnalyzer() = default;

		std::vector<std::string> &getLibs();
		std::vector<std::string> &getGames();
	protected:
	private:
		void _analyzeFolder(const std::string &,
					std::vector<std::string> &);
		std::vector<std::string> _libs;
		std::vector<std::string> _games;
};
