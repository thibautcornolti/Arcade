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
#include <map>
#include "Scoreboard.hpp"

Arcade::Scoreboard::Scoreboard(const std::string &gameName, const std::string &playerName) :_gameName(gameName), _playerName(playerName)
{
	readScores();
}

Arcade::Scoreboard::~Scoreboard() {}

void Arcade::Scoreboard::readScores()
{
	std::fstream file(SCOREBOARD, std::ios::in);
	std::string line;
	std::vector<std::string> tokens;

	if (!file)
		return ;
	_scores.clear();
	while(getline(file, line)) {
		if (!line.find(_gameName)) {
			std::istringstream split(line);
			for(std::string each; std::getline(split, each, ':'); tokens.push_back(each));
			break;
		}
	}
	for (size_t i = 1; i < tokens.size(); i += 2)
		_scores.push_back({tokens[i], std::stol(tokens[i + 1])});
}

void Arcade::Scoreboard::addPlayerToScoreboard(int place)
{
	_scores[place].first = _playerName;
	_scores[place].second = _score;
}

void Arcade::Scoreboard::updateScoreboard()
{
	int place = 3;

	for (auto &player : _scores) {
		if (player.second < _score && place != 0)
			place--;
	}
	if (place < 3)
		addPlayerToScoreboard(place);
}

std::string Arcade::Scoreboard::getFormattedScoreboard() const
{
	std::string scoresFormatted = _gameName;

	for (size_t i = 0; i < _scores.size(); i++) {
		scoresFormatted += ":" + _scores[i].first + ":" + std::to_string(_scores[i].second);
	}
	return scoresFormatted;
}

void Arcade::Scoreboard::saveScoreboard()
{
	std::fstream file(SCOREBOARD, std::ios::out | std::ios::in);
	std::string line;
	std::vector<std::string> allScores;
	std::string scoresFormatted = getFormattedScoreboard();
	int linePos = 0;

	if (!file)
		return;
	while(getline(file, line)) {
		if (line.find(_gameName))
			linePos++;
		allScores.push_back(line);
	}
	file.clear();
	file.seekp(0, std::ios::beg);
	allScores[linePos] = scoresFormatted;
	for (auto &elem : allScores)
		file << elem << std::endl;
}

std::vector<std::pair<std::string, size_t>> Arcade::Scoreboard::getScoreboard() const
{
	return _scores;
}

size_t Arcade::Scoreboard::getScores() const
{
	return _score;
}

void Arcade::Scoreboard::addScores(const size_t &points)
{
	_score += points;

	if (_score > _scores.back().second)
		updateScoreboard();
}

void Arcade::Scoreboard::subScores(const size_t &points)
{
	_score -= points;
}