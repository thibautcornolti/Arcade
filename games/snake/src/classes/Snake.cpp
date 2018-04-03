/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <iostream>
#include <ctime>
#include <zconf.h>
#include <chrono>
#include <thread>
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
	_map.replace(_map.size() / 2, 4, 4, '0');
	for (size_t i = 0; i < _map.size(); i++) {
		pos.first = i % (MAP + 2);
		pos.second = i / (MAP + 2);
		if (pos.first == 0 || pos.second == 0 ||
			pos.first == MAP + 1 || pos.second == MAP + 1)
			_map[i] = '#';
	}
	addFood();
	for (int i = 0; i < 4; i++) {
		snakePos = _map.size() / 2 + i;
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

bool Arcade::Snake::restart()
{
	_map.clear();
	_snake.clear();
	_current = RIGHT;
	_game = RUNNING;
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
		case Arcade::Keys::P: //Pause
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

void Arcade::Snake::refresh(IGraphicLib *lib)
{
	static bool run = true;

	if (run) {
		lib->clearWindow();
		if (_game != PAUSED) {
			std::this_thread::sleep_for(std::chrono::milliseconds(SPEED));
			move();
			if (collide()) {
				_game = ENDED;
				run = false;
			}
		}
		display(lib);
		lib->refreshWindow();
	}
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

void Arcade::Snake::displayGameInfo(IGraphicLib *lib)
{
	Arcade::TextBox title("Snake", {(lib->getMaxX() - 5) / 2, 5});
	Arcade::TextBox statut("Statut: ", {(lib->getMaxX() - 5) / 2, 7});
	Arcade::TextBox score("Score: ", {(lib->getMaxX() - 5) / 2, 8});
	Arcade::TextBox scoreb("Scoreboard", {(lib->getMaxX()) / 3 * 2 + 10, 7});

	statut.setValue(statut.getValue() + getStatus());
	statut.setX((lib->getMaxX() - statut.getValue().size()) / 2);
	lib->drawText(title);
	lib->drawText(statut);
	lib->drawText(score);
	lib->drawText(scoreb);
}

void Arcade::Snake::display(IGraphicLib *lib)
{
	Arcade::PixelBox map({MAP + 2, MAP + 2},
		{(lib->getMaxX() - MAP) / 2, (lib->getMaxY() - MAP) / 2});
	updatePixel(map);
	displayGameInfo(lib);
	lib->drawPixelBox(map);
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
	if (_map.find_first_of('1', 0) == std::string::npos) {
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
			_map[nextLinkPos] = '0';
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
			_map[pos] = '1';
			running = false;
		}

	}
}