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

Arcade::Scoreboard::Scoreboard(const std::string &gameName) :_gameName(gameName)
{
	_scores = readScores();
}

Arcade::Scoreboard::~Scoreboard()
{
	int place = 3;

	for (auto &player : _scores) {
		while (player.second < _score && place != 0)
			place--;
	}
	if (place < 3)
		addPlayerToScoreboard(place);
}

std::vector<std::pair<std::string, size_t>> Arcade::Scoreboard::readScores() const
{
	std::fstream file(SCOREBOARD, std::ios::in);
	std::string line;
	std::vector<std::pair<std::string, size_t>> score;
	std::vector<std::string> tokens;

	if (!file)
		return score;
	while(getline(file, line)) {
		if (!line.find(_gameName)) {
			std::istringstream split(line);
			for(std::string each; std::getline(split, each, ':'); tokens.push_back(each));
			break;
		}
	}
	for (size_t i = 1; i < tokens.size(); i += 2)
		score.push_back({tokens[i], std::stol(tokens[i + 1])});
	return score;
}

void Arcade::Scoreboard::addPlayerToScoreboard(int place)
{
	_scores[place].first = "Unknown";
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
	if (_score > _scores.end()->second)
		updateScoreboard();
}

void Arcade::Scoreboard::removeScores(const size_t &points)
{
	_score -= points;
}

int main() {
	Arcade::Scoreboard score("Snake");

	for (auto &test : score.getScoreboard()) {
		std::cout << test.first << test.second << std::endl;
	}
	return 0;
}