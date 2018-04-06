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
	_scale = new Scale();
}

Arcade::Snake::~Snake()
{
}

const std::string Arcade::Snake::getName() const
{
	return _name;
}

std::string Arcade::Snake::getPlayerName() const
{
	return _playerName;
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
	_map.erase(std::remove(_map.begin(), _map.end(), '\n'), _map.end());
	_time = std::chrono::high_resolution_clock::now();
	std::srand(std::time(nullptr));
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

bool Arcade::Snake::restart()
{
	_map.clear();
	_snake.clear();
	_current = RIGHT;
	_game = RUNNING;
	_score->resetScores();
	init();
	return true;
}

bool Arcade::Snake::applyEvent(Arcade::Keys key)
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
		case Arcade::Keys::C:
			_game = (_game == CHEAT) ? RUNNING : CHEAT;
			break;
		default:
			break ;
	}
	return true;
}

bool Arcade::Snake::update()
{
	return true;
}

void Arcade::Snake::refresh(IGraphicLib &lib)
{
	lib.clearWindow();
	if ((_game == RUNNING || _game == CHEAT) && isTimeToMove()) {
		move();
		food();
	}
	display(lib);
	lib.refreshWindow();
}

size_t Arcade::Snake::getScore()
{
	return _score->getScores();
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
		case CHEAT:
			return "GODMODE";
		default:
			return "Ended";
	}
}

static const std::map<const std::string, const Arcade::Vect<double>> _text = {
	{"Snake", {47, 1}},
	{"Statut: ", {42, 2}},
	{"Score: ", {45, 3}},
};

void Arcade::Snake::displayGameInfo(IGraphicLib &lib)
{
	Arcade::TextBox text("Ramdom", {0, 0}, 20);

	for (auto &elem : _text) {
		if (!elem.first.find("Statut"))
			text.setValue(elem.first + getStatus());
		else if (!elem.first.find("Score"))
			text.setValue(elem.first + std::to_string(_score->getScores()));
		else
			text.setValue(elem.first);
		_scale->scaleTextBox(elem.second, text);
		lib.drawText(text);
	}
}

void Arcade::Snake::display(IGraphicLib &lib)
{
	Arcade::PixelBox pixelMap({MAP + 2, MAP + 2}, {0, 0});

	updatePixel(pixelMap);
	_scale->setCentering(Scale::CENTERING::BOTH);
	_scale->setWindowSize({lib.getMaxX(), lib.getMaxY()});
	_scale->scalePixelBox({50, 50}, {50, 50}, pixelMap);
	displayGameInfo(lib);
	lib.drawPixelBox(pixelMap);
}

void Arcade::Snake::setMove(Arcade::Snake::MOVE move)
{
	_current = move;
}

bool Arcade::Snake::food()
{
	if (_map.find_first_of('2', 0) == std::string::npos) {
		_score->addScores(10);
		addFood();
		addLink();
	}
	return false;
}

void Arcade::Snake::addLink()
{
	t_snake snake = _snake.back();

	_snake.push_back(snake);
}

bool Arcade::Snake::collide(size_t &currentPos)
{
	if (_map[currentPos + _current] != ' ' &&
		_map[currentPos + _current] != '2') {
		if (_game != CHEAT) {
			_game = ENDED;
		}
		return true;
	}
	return false;
}

bool Arcade::Snake::move()
{
	size_t nextLinkPos;

	for (auto it = _snake.begin(); it != _snake.end(); ++it) {
		if (it == _snake.begin()) {
			if (collide(it->currentPos))
				return false;
			_map[it->currentPos] = ' ';
			_map[it->currentPos + _current] = '0';
			it->lastPos = it->currentPos;
			it->currentPos += _current;
		} else {
			_map[it->currentPos] = ' ';
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