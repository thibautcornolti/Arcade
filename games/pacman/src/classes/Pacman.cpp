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

void Arcade::Pacman::applyEvent(Arcade::Keys)
{

}

void Arcade::Pacman::update()
{

}

void Arcade::Pacman::refresh(IGraphicLib &lib)
{
    if (!_init) {
        _pixelMap = Arcade::PixelBox({MAP_WIDTH, MAP_HEIGHT},
            {lib.getMaxX() / 2 - MAP_WIDTH / 2,
            lib.getMaxY() / 2 - MAP_HEIGHT / 2});
        _init = true;
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
    dprintf(2, "%s\n", _map);
    return true;
}

Arcade::Vect<size_t> Arcade::Pacman::getCoords(size_t pos) const
{
    return {pos % (MAP_WIDTH + 2), pos / (MAP_HEIGHT + 2)};
}

void Arcade::Pacman::display(Arcade::IGraphicLib &lib)
{
    updatePixel();
    lib.drawPixelBox(_pixelMap);
}

void Arcade::Pacman::updatePixel()
{
    for (size_t i = 0; i < _map.size(); ++i) {
        switch (_map[i]) {
            case '#':
                _pixelMap.putPixel(getCoords(i), {255, 0, 0, 255});
                break;
            case '*':
                _pixelMap.putPixel(getCoords(i), {0, 255, 0, 255});
                break;
            case 'P':
                _pixelMap.putPixel(getCoords(i), {255, 255, 0, 255});
                break;
            default:
                _pixelMap.putPixel(getCoords(i), {0, 0, 0, 255});
                break;
        }
    }
}

void Arcade::Pacman::setPlayerName(const std::string &name)
{

}
