/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
#include <algorithm>
#include <sstream>
#include "Snake.hpp"

Arcade::Snake::Snake()
{
	_score = new Scoreboard(_name, _playerName);
}

Arcade::Snake::~Snake()
{
}

const std::string Arcade::Snake::getName() const
{
	return _name;
}

void Arcade::Snake::setPlayerName(const std::string &playerName)
{
	_playerName = playerName;
}

std::string Arcade::Snake::getPlayerName() const
{
	return _playerName;
}

void Arcade::Snake::initArcadeElements(Arcade::IGraphicLib &lib)
{
	Arcade::PixelBox pixelMap(
		{MAP + 2, MAP + 2},
		{(lib.getMaxX() - MAP) / 2, (lib.getMaxY() - MAP) / 2});
	_pixelMap = pixelMap;
	_isRunning = true;
}

bool Arcade::Snake::init()
{
	std::fstream file(ASSETS_PATH, std::ios::in);
	std::stringstream buf;
	size_t snakePos;

	if (!file)
		return false;
	buf << file.rdbuf();
	_map = buf.str();
	_time = std::chrono::high_resolution_clock::now();
	std::srand(std::time(nullptr));
	_map.erase(std::remove(_map.begin(), _map.end(), '\n'), _map.end());
	addFood();
	snakePos = _map.find_first_of('0');
	for (size_t i = snakePos; i < snakePos + 4; i++)
		_snake.push_front({i, i});
	return true;
}

bool Arcade::Snake::stop()
{
	return true;
}

bool Arcade::Snake::open()
{
	return true;
}

bool Arcade::Snake::close()
{
	return true;
}

bool Arcade::Snake::restart()
{
	_map.clear();
	_snake.clear();
	_current = RIGHT;
	_game = RUNNING;
	_isRunning = false;
	init();
	return true;
}

void Arcade::Snake::applyEvent(Arcade::Keys key)
{
	switch (key) {
		case Arcade::Keys::Z:
			if (_current != BOT)
				setMove(TOP);
			break ;
		case Arcade::Keys::S:
			if (_current != TOP)
				setMove(BOT);
			break ;
		case Arcade::Keys::D:
			if (_current != LEFT)
				setMove(RIGHT);
			break ;
		case Arcade::Keys::Q:
			if (_current != RIGHT)
				setMove(LEFT);
			break ;
		case Arcade::Keys::P:
			_game = (_game == PAUSED) ? RUNNING : PAUSED;
			break;
		case Arcade::Keys::R:
			restart();
			break;
		default:
			break ;
	}
}

void Arcade::Snake::update()
{
}

void Arcade::Snake::refresh(IGraphicLib &lib)
{
	if (!_isRunning)
		initArcadeElements(lib);
	lib.clearWindow();
	if (_game == RUNNING && isTimeToMove()) {
		move();
		if (collide())
			_game = ENDED;
	}
	display(lib);
	lib.refreshWindow();
}

bool Arcade::Snake::isTimeToMove()
{
	auto time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double, std::milli>(time-_time).count();

	if (duration >= SPEED) {
		_time = time;
		return true;
	}
	return false;
}

Arcade::Vect<size_t> Arcade::Snake::getCoords(size_t pos) const
{
	return {pos % (MAP + 2), pos / (MAP + 2)};
}

void Arcade::Snake::updatePixel(Arcade::PixelBox &map)
{
	char key;

	for (size_t i = 0; i < _map.size(); i++) {
		key = _map[i];
		switch (key) {
			case '#':
				map.putPixel(getCoords(i), {255, 0, 0, 255});
				break;
			case '0':
				map.putPixel(getCoords(i), {255, 255, 0, 255});
				break;
			case '1':
				map.putPixel(getCoords(i), {0, 0, 255, 255});
				break;
			case '2':
				map.putPixel(getCoords(i), {0, 255, 0, 255});
				break;
			default:
				map.putPixel(getCoords(i), {0, 0, 0, 255});
				break;
		}
	}
}

std::string Arcade::Snake::getStatus() const
{
	switch (_game) {
		case RUNNING:
			return "Running";
		case PAUSED:
			return "Paused";
		default:
			return "Ended";
	}
}

void Arcade::Snake::displayScoreboard(Arcade::IGraphicLib &)
{
	auto scores = _score->getScoreboard();
}

void Arcade::Snake::displayGameInfo(IGraphicLib &lib)
{
	Arcade::TextBox title("Snake", {(lib.getMaxX() - 5) / 2, 5}, 20);
	Arcade::TextBox statut("Statut: ", {(lib.getMaxX() - 5) / 2, 7}, 20);
	Arcade::TextBox score("Score: ", {(lib.getMaxX() - 5) / 2, 8}, 20);
	Arcade::TextBox scoreb("Scoreboard", {(lib.getMaxX()) / 3 * 2 + 10, 7}, 20);

	statut.setValue(statut.getValue() + getStatus());
	statut.setX((lib.getMaxX() - statut.getValue().size()) / 2);
	score.setValue(score.getValue() + std::to_string(_score->getScores()));
	score.setX((lib.getMaxX() - score.getValue().size()) / 2);
	lib.drawText(title);
	lib.drawText(statut);
	lib.drawText(score);
	lib.drawText(scoreb);
}

void Arcade::Snake::display(IGraphicLib &lib)
{
	if (_game == RUNNING)
		updatePixel(_pixelMap);
	displayGameInfo(lib);
	lib.drawPixelBox(_pixelMap);
}

void Arcade::Snake::setMove(Arcade::Snake::MOVE move)
{
	_current = move;
}

bool Arcade::Snake::collide()
{
	size_t headLink = _snake.front().currentPos;
	Arcade::Vect<size_t> coord = getCoords(headLink);
	int escapeHead = 0;

	for (auto &&it : _snake) {
		if (escapeHead != 0)
			if (headLink == it.currentPos)
				return true;
		escapeHead++;
	}
	if (_map.find_first_of('2', 0) == std::string::npos) {
		_score->addScores(10);
		addFood();
		addLink();
	}
	if (coord.getX() == 0 || coord.getY() == 0 ||
	    coord.getX() == MAP + 1 || coord.getY() == MAP + 1)
		return true;
	return false;
}

void Arcade::Snake::addLink()
{
	t_snake snake = _snake.back();

	_snake.push_back(snake);
}


bool Arcade::Snake::move()
{
	size_t nextLinkPos;

	for (auto it = _snake.begin(); it != _snake.end(); ++it) {
		_map[it->currentPos] = ' ';
		if (it == _snake.begin()) {
			_map[it->currentPos + _current] = '0';
			it->lastPos = it->currentPos;
			it->currentPos += _current;
		} else {
			std::advance(it, -1);
			nextLinkPos = it->lastPos;
			std::advance(it, 1);
			_map[nextLinkPos] = '1';
			it->lastPos = it->currentPos;
			it->currentPos = nextLinkPos;
		}
	}
	return true;
}

void Arcade::Snake::addFood()
{
	Arcade::Vect<size_t> coord;
	bool running = true;
	size_t pos;

	while (running) {
		pos = std::rand() % _map.size();
		coord = getCoords(pos);
		if (coord.getX() >= 1 && coord.getY() >= 1 &&
			coord.getX() <= MAP + 1 && coord.getY() <= MAP + 1 &&
			_map[pos] == ' ') {
			_map[pos] = '2';
			running = false;
		}

	}
}