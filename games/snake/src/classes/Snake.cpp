/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <iostream>
#include <ctime>
#include <zconf.h>
#include "Snake.hpp"

Arcade::Snake::Snake()
{
}

Arcade::Snake::~Snake()
{
}

const std::string &Arcade::Snake::getName() const
{
	return _name;
}

bool Arcade::Snake::init()
{
	_map = std::string((MAP + 2) * (MAP + 2), ' ');
	std::pair<size_t , size_t> pos;
	t_snake snake;
	size_t snakePos;

	std::srand(std::time(nullptr));
	_map.replace(_map.size() / 2 + 20, 4, 4, '0');
	for (size_t i = 0; i < _map.size(); i++) {
		pos.first = i % (MAP + 2);
		pos.second = i / (MAP + 2);
		if (pos.first == 0 || pos.second == 0 ||
			pos.first == MAP + 1 || pos.second == MAP + 1)
			_map[i] = '#';
	}
	addFood();
	for (int i = 0; i < 4; i++) {
		snakePos = _map.size() / 2 + (MAP / 2 + i);
		snake = {3 - i, snakePos, snakePos};
		_snake.push_front(snake);
	}
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

void Arcade::Snake::applyEvent(Arcade::Keys key)
{
	switch (key) {
		case Arcade::Keys::Z:
			setMove(TOP);
			break ;
		case Arcade::Keys::S:
			setMove(BOT);
			break ;
		case Arcade::Keys::D:
			setMove(RIGHT);
			break ;
		case Arcade::Keys::Q:
			setMove(LEFT);
			break ;
		default:
			break ;
	}
}

void Arcade::Snake::update()
{
	if (_game == ENDED) {
		init();
		_game = RUNNING;
	}
}

void Arcade::Snake::refresh(IGraphicLib *lib)
{
	lib->clearWindow();
	move();
	display(lib);
	lib->refreshWindow();
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
				map.putPixel(getCoords(i), {0, 0, 255, 255});
				break;
			case '1':
				map.putPixel(getCoords(i), {0, 255, 0, 255});
				break;
			default:
				map.putPixel(getCoords(i), {0, 0, 0, 255});
				break;
		}
	}
}

void Arcade::Snake::display(IGraphicLib *lib)
{
	Arcade::PixelBox map({MAP + 2, MAP + 2},
		{(lib->getMaxX() - MAP) / 2, (lib->getMaxY() - MAP) / 2});
	updatePixel(map);
	lib->drawPixelBox(map);
}

void Arcade::Snake::setMove(const Arcade::Snake::MOVE move)
{
	_current = move;
}

bool Arcade::Snake::move()
{
	usleep(SPEED);
	size_t nextLinkPos;

	for (auto it = _snake.begin(); it != _snake.end(); it++) {
		_map[it->currentPos] = ' ';
		if (it == _snake.begin()) {
			_map[it->currentPos + _current] = '0';
			it->lastPos = it->currentPos;
			it->currentPos += _current;
		} else {
			std::advance(it, -1);
			nextLinkPos = it->lastPos;
			std::advance(it, 1);
			_map[nextLinkPos] = '0';
			it->lastPos = it->currentPos;
			it->currentPos = nextLinkPos;
		}
	}
	return true;
}

void Arcade::Snake::addFood()
{
	bool running = true;
	size_t pos;
	Arcade::Vect<size_t> coord;

	while (running) {
		pos = std::rand() % _map.size();
		coord = getCoords(pos);
		if (coord.getX() >= 1 && coord.getY() >= 1 &&
			coord.getX() <= MAP + 1 && coord.getY() <= MAP + 1 &&
			_map[pos] == ' ') {
			_map[pos] = '1';
			running = false;
		}

	}
}