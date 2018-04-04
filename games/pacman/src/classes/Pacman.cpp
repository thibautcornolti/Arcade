/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman.cpp
*/

#include <sstream>
#include <algorithm>
#include "Pacman.hpp"

Arcade::Pacman::Pacman()
{
    _score = new Scoreboard(_name, _playerName);
    _scale = new Scale();
}

Arcade::Pacman::~Pacman()
{

}

const std::string Arcade::Pacman::getName() const
{
    return _name;
}

bool Arcade::Pacman::init()
{
    _player = PacPlayer();
    _ghosts.assign(4, Ghost());
    if (!readMap())
        return false;
    _current_pos = findPlayer();
    if (_current_pos == UINT32_MAX) {
        std::cerr << "Can not find initial player position in map" << std::endl;
        return false;
    }
    return true;
}

bool Arcade::Pacman::stop()
{
    return false;
}

bool Arcade::Pacman::open()
{
    return false;
}

bool Arcade::Pacman::close()
{
    return false;
}

bool Arcade::Pacman::restart()
{

}

void Arcade::Pacman::applyEvent(Arcade::Keys key)
{
    switch (key) {
        case Arcade::Keys::Z:
            _move = Arcade::Pacman::MOVE::TOP;
            break;
        case Arcade::Keys::S:
            _move = Arcade::Pacman::MOVE::BOT;
            break;
        case Arcade::Keys::Q:
            _move = Arcade::Pacman::MOVE::LEFT;
            break;
        case Arcade::Keys::D:
            _move = Arcade::Pacman::MOVE::RIGHT;
            break;
        case Arcade::Keys::P:
            _status = (_status == PAUSED) ? RUNING : PAUSED;
            break;
        case Arcade::Keys::R:
            restart();
            break;
        default:
            _move = Arcade::Pacman::MOVE::STILL;
            break;
    }
}

void Arcade::Pacman::update()
{

}

void Arcade::Pacman::refresh(IGraphicLib &lib)
{
        _pixelMap = Arcade::PixelBox({MAP_WIDTH, MAP_HEIGHT + 3},
            {lib.getMaxX() / 2 - MAP_WIDTH / 2,
            lib.getMaxY() / 2 - MAP_HEIGHT / 2});
        _init = true;
        _status = Arcade::Pacman::STATUS::RUNING;
    if (_status == Arcade::Pacman::STATUS::RUNING &&
        _move != Arcade::Pacman::MOVE::STILL) {
        move();
    }
    lib.clearWindow();
    display(lib);
    lib.refreshWindow();
}

bool Arcade::Pacman::readMap()
{
    std::fstream f(ASSETS_PATH, std::ios::in);
    std::stringstream buf;

    if (!f)
        return false;
    buf << f.rdbuf();
    _map = buf.str();
    _map.erase(std::remove(_map.begin(), _map.end(), '\n'), _map.end());
    std::cerr << _map.length() << std::endl;
	std::cerr << MAP_WIDTH * MAP_HEIGHT << std::endl;
    return true;
}

Arcade::Vect<size_t> Arcade::Pacman::getCoords(size_t pos) const
{
    return {pos % (MAP_WIDTH), pos / (MAP_HEIGHT)};
}

void Arcade::Pacman::display(Arcade::IGraphicLib &lib)
{
    updatePixel();
    _scale->setCentering(Scale::BOTH);
    _scale->setWindowSize({lib.getMaxX(), lib.getMaxY()});
    _scale->scalePixelBox({50, 50}, {25, 50}, _pixelMap);
    lib.drawPixelBox(_pixelMap);
}

void Arcade::Pacman::updatePixel()
{
	for (size_t i = 0; i < _map.size(); ++i) {
		switch (_map[i]) {
			case '#':
				_pixelMap.putPixel(getCoords(i),
				                   {255, 0, 0, 255});
				break;
			case '*':
				_pixelMap.putPixel(getCoords(i),
				                   {0, 255, 0, 255});
				break;
			case 'P':
				_pixelMap.putPixel(getCoords(i),
				                   {255, 255, 0, 255});
				break;
			case '.':
				_pixelMap.putPixel(getCoords(i),
				                   {0, 0, 255, 255});
				break;
			default:
				_pixelMap.putPixel(getCoords(i),
				                   {0, 0, 0, 255});
				break;
		}
	}
}

void Arcade::Pacman::setPlayerName(const std::string &name)
{

}

void Arcade::Pacman::move()
{
    if (_map[_current_pos + _move] == '#') {
        _move = Arcade::Pacman::MOVE::STILL;
        return;
    }
    /*if (_map[_current_pos] == '.')
        _score->addScores(10);*/
    _map[_current_pos] = ' ';
    _current_pos += _move;
    _map[_current_pos] = 'P';
}

size_t Arcade::Pacman::findPlayer()
{
    for (size_t i = 0; i < _map.size(); ++i) {
        if (_map[i] == 'P')
            return i;
    }
    return UINT32_MAX;
}