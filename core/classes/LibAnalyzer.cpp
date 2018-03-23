/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "LibAnalyzer.hpp"
#include <iostream>

LibAnalyzer::LibAnalyzer()
{
	_analyzeFolder(GAME_FOLDER, _games);
	_analyzeFolder(GRAPH_FOLDER, _graphs);
}

void LibAnalyzer::_analyzeFolder(const std::string &path,
					std::vector<std::string> &container)
{
	DIR *dir;
	struct dirent *ent;
	std::string end(".so");

	dir = opendir(path.c_str());
	if (dir) {
		while ((ent = readdir(dir))) {
			std::string name(ent->d_name);
			if (name.length() > 3 && std::equal(name.begin() +
			name.size() - end.size(), name.end(), end.begin()))
				container.push_back(ent->d_name);
		}
		closedir(dir);
	} else {
		perror(path.c_str());
	}
}

std::vector<std::string> &LibAnalyzer::getGraphs()
{
	return _graphs;
}

std::vector<std::string> &LibAnalyzer::getGames()
{
	return _games;
}
