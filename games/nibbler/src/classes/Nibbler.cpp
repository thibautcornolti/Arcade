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
#include "Nibbler.hpp"

Arcade::Nibbler::Nibbler()
{
	_score = new Scoreboard();
	_scale = new Scale();
}

Arcade::Nibbler::~Nibbler()
{
}

const std::string Arcade::Nibbler::getName() const
{
	return _name;
}

std::string Arcade::Nibbler::getPlayerName() const
{
	return _playerName;
}

void Arcade::Nibbler::initMap()
{
	_map = "###########################"
	"#                         #"
 	"#     #             #     #"
  	"# ###                 ### #"
   	"#                         #"
    	"#                         #"
     	"#                         #"
      	"#                         #"
       	"#                         #"
	"#                         #"
 	"#                         #"
  	"#                         #"
   	"#                         #"
    	"#           0001          #"
     	"#                         #"
      	"#                         #"
       	"#                         #"
	"#                         #"
 	"#                         #"
  	"#                         #"
   	"#                         #"
    	"#                         #"
     	"#                         #"
      	"# ###                 ### #"
       	"#     #             #     #"
	"#                         #"
 	"###########################";
}

bool Arcade::Nibbler::init()
{
	size_t nibblerPos;

	initMap();
	_time = std::chrono::high_resolution_clock::now();
	std::srand(std::time(nullptr));
	addFood();
	nibblerPos = _map.find_first_of('0');
	for (size_t i = nibblerPos; i < nibblerPos + 4; i++)
		_nibbler.push_front({i, i});
	return true;
}

bool Arcade::Nibbler::stop()
{
	_map.clear();
	_nibbler.clear();
	_current = RIGHT;
	_game = RUNNING;
	_gameOverTimer = 10;
	_score->resetScores();
	return true;
}

bool Arcade::Nibbler::restart()
{
	_map.clear();
	_nibbler.clear();
	_current = RIGHT;
	_game = RUNNING;
	_gameOverTimer = 10;
	_score->resetScores();
	init();
	return true;
}

bool Arcade::Nibbler::applyEvent(Arcade::Keys key)
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
			if (_game == CHEAT)
				_gameOverTimer = 10;
			break;
		default:
			break ;
	}
	return true;
}

bool Arcade::Nibbler::update()
{
	if (_game == ENDED)
		return false;
	return true;
}

void Arcade::Nibbler::gameOver(IGraphicLib &lib)
{
	auto time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double, std::milli>(time-_gameOver).count();
	Arcade::TextBox gameover("Game Over", {0, 0});
	Arcade::TextBox gameCounter("SinonCaSEGV", {0, 1});
	Arcade::TextBox help("Press R to restart", {0, 1});

	gameCounter.setValue(std::to_string(_gameOverTimer));
	_scale->scaleTextBox({0, 0}, gameover);
	_scale->scaleTextBox({10, 1}, gameCounter);
	_scale->scaleTextBox({0, 1.8}, help);
	if (duration >= 1000) {
		_gameOver = time;
		_gameOverTimer--;
	}
	if (_gameOverTimer == 0)
		_game = ENDED;
	lib.drawText(gameover);
	lib.drawText(gameCounter);
	lib.drawText(help);
}

void Arcade::Nibbler::refresh(IGraphicLib &lib)
{
	lib.clearWindow();
	if ((_game == RUNNING || _game == CHEAT) && isTimeToMove()) {
		move();
		food();
	}
	if (_game == WAITING)
		gameOver(lib);
	display(lib);
	lib.refreshWindow();
}

size_t Arcade::Nibbler::getScore()
{
	return _score->getScores();
}

bool Arcade::Nibbler::isTimeToMove()
{
	auto time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<double, std::milli>(time-_time).count();

	if (duration >= _speed) {
		_time = time;
		return true;
	}
	return false;
}

Arcade::Vect<size_t> Arcade::Nibbler::getCoords(size_t pos) const
{
	return {pos % (MAP + 2), pos / (MAP + 2)};
}

void Arcade::Nibbler::updatePixel(Arcade::PixelBox &map)
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

std::string Arcade::Nibbler::getStatus() const
{
	switch (_game) {
		case RUNNING:
			return "Running";
		case PAUSED:
			return "Paused";
		case CHEAT:
			return "GODMODE";
		case WAITING:
			return "Waiting";
		default:
			return "Ended";
	}
}

static const std::map<const std::string, const Arcade::Vect<double>> _text = {
	{"Nibbler", {47, 1}},
	{"Statut: ", {42, 2}},
	{"Score: ", {45, 3}},
};

void Arcade::Nibbler::displayGameInfo(IGraphicLib &lib)
{
	Arcade::TextBox text("Ramdom", {0, 0}, 20);
	Arcade::TextBox help("Press P for pause", {0, 0});
	Arcade::TextBox cheat("Press C for cheat :p", {0, 1});

	_scale->scaleTextBox({0, 1}, cheat);
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
	if (_game != WAITING) {
		lib.drawText(help);
		lib.drawText(cheat);
	}
}

void Arcade::Nibbler::display(IGraphicLib &lib)
{
	Arcade::PixelBox pixelMap({MAP + 2, MAP + 2}, {0, 0});

	updatePixel(pixelMap);
	_scale->setCentering(Scale::CENTERING::BOTH);
	_scale->setWindowSize({lib.getMaxX(), lib.getMaxY()});
	_scale->scalePixelBox({50, 55}, {75, 75}, pixelMap);
	displayGameInfo(lib);
	lib.drawPixelBox(pixelMap);
}

void Arcade::Nibbler::setMove(Arcade::Nibbler::MOVE move)
{
	_current = move;
}

bool Arcade::Nibbler::food()
{
	if (_map.find_first_of('2', 0) == std::string::npos) {
		_score->addScores(10);
		_speed -= 1;
		addFood();
		addLink();
	}
	return false;
}

void Arcade::Nibbler::addLink()
{
	t_nibbler nibbler = _nibbler.back();

	_nibbler.push_back(nibbler);
}

bool Arcade::Nibbler::collide(size_t &currentPos)
{
	if (_map[currentPos + _current] != ' ' &&
		_map[currentPos + _current] != '2') {
		if (_game != CHEAT) {
			_game = WAITING;
		}
		return true;
	}
	return false;
}

bool Arcade::Nibbler::move()
{
	size_t nextLinkPos;

	for (auto it = _nibbler.begin(); it != _nibbler.end(); ++it) {
		if (it == _nibbler.begin()) {
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

void Arcade::Nibbler::addFood()
{
	bool running = true;
	size_t pos;

	while (running) {
		pos = std::rand() % _map.size();
		if (_map[pos] == ' ') {
			_map[pos] = '2';
			running = false;
		}

	}
}