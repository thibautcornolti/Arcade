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
#include "Scoreboard.hpp"

Arcade::Scoreboard::Scoreboard() {}

Arcade::Scoreboard::~Scoreboard() {}

bool Arcade::Scoreboard::readScoreboard()
{
	std::fstream file(SCOREBOARD);
	std::vector<std::string> tokens;
	std::string line;

	if (!file)
		return false;
	while(getline(file, line)) {
		std::istringstream split(line);
		for(std::string each; std::getline(split, each, ':'); tokens.push_back(each));
		_allScores[tokens.front()] = tokens;
		tokens.clear();
	}
	return true;
}

std::map<const std::string, std::vector<std::string>> Arcade::Scoreboard::getScoreboard() const
{
	return _allScores;
}

size_t Arcade::Scoreboard::getLastPlayerScore() const
{
	return _allScoresComputed.back().second;
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