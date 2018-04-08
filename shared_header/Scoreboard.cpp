/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scoreboard.cpp
*/

#include <iostream>
#include <fstream>
#include <ios>
#include <sstream>
#include <regex>
#include "Scoreboard.hpp"

Arcade::Scoreboard::Scoreboard() {}

Arcade::Scoreboard::~Scoreboard() {}

bool Arcade::Scoreboard::readScoreboard()
{
	std::fstream file(SCOREBOARD);
	std::cmatch cm;
	std::string line;

	if (!file)
		return false;
	while (getline(file, line)) {
		if (std::regex_match(line.c_str(), cm, std::regex("^([A-Za-z]+):(([A-Za-z]+)\\s+([0-9]+)):(([A-Za-z]+)\\s+([0-9]+)):(([A-Za-z]+)\\s+([0-9]+))$"))) {
			_allScores[cm[1]] = {cm[2], cm[5], cm[8]};
			_allScoresComputed[cm[1]] = {{cm[3], std::stol(cm[4])}, {cm[6], std::stol(cm[7])}, {cm[9], std::stol(cm[10])}};
		} else
			return false;
	}
	return true;
}

size_t Arcade::Scoreboard::getLastPlayerScore()
{
	return _allScoresComputed[_gameName].back().second;
}


std::map<std::string, std::vector<std::string>> Arcade::Scoreboard::getScoreboard() const
{
	return _allScores;
}

void Arcade::Scoreboard::setGameName(const std::string &gameName)
{
	_gameName = gameName;
}

void Arcade::Scoreboard::setPlayerName(const std::string &playerName)
{
	_playerName = playerName;
}

size_t Arcade::Scoreboard::getScores() const
{
	return _score;
}

void Arcade::Scoreboard::addScores(const size_t &points)
{
	_score += points;
}

void Arcade::Scoreboard::subScores(const size_t &points)
{
	_score -= points;
}

void Arcade::Scoreboard::resetScores()
{
	_score = 0;
}