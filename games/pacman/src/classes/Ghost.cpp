/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Ghost.cpp
*/

#include <unistd.h>
#include <cstring>
#include "Ghost.hpp"

Arcade::Ghost::Ghost(std::string &map, const std::string &name, Arcade::Pacman &pac) :
        _map(map),
        _name(name),
        _pac(pac)
{
        _time = std::chrono::high_resolution_clock::now();
}

Arcade::Ghost::~Ghost()
{

}

bool Arcade::Ghost::placeGhost()
{
        for (size_t i = 0; i < _map.size(); ++i) {
                if (_map[i] == '+') {
                        std::cerr << "Placing ghost" << std::endl;
                        _initialPos = i;
                        _currentPos = i;
                        _map[i] = 'G';
                        break;
                }
        }
        return true;
}


void print_map(std::string map)
{
        for (int i = 0; i < MAP_HEIGHT + 3; ++i) {
                for (int j = 0; j < MAP_WIDTH; ++j) {
                        if (map[i * MAP_WIDTH + j] == 'o') {
                                write(2, "\033[1m\033[31m", strlen("\033[1m\033[31m"));
                                std::cerr << map[i * MAP_WIDTH + j];
                                write(2, "\033[0m", strlen("\033[0m"));
                        }
                        else if (map[i * MAP_WIDTH + j] == '.') {
                                write(2, "\033[1m\033[33m", strlen("\033[1m\033[33m"));
                                std::cerr << map[i * MAP_WIDTH + j];
                                write(2, "\033[0m", strlen("\033[0m"));
                        }
                        else
                                std::cerr << map[i * MAP_WIDTH + j];
                }
                std::cerr << std::endl;
        }
        std::cerr << std::endl;
}

bool Arcade::Ghost::move()
{
        Vect<size_t> pos = getCoords(_currentPos);

        if (!isTimeToMove())
                return false;
        _tmp = _map;
        std::replace(_tmp.begin(), _tmp.end(), '.', ' ');
        std::replace(_tmp.begin(), _tmp.end(), '*', ' ');
        std::replace(_tmp.begin(), _tmp.end(), '|', '#');
        //print_map(_tmp);
        std::cerr << _compute << std::endl;
        if (_compute == 0) {
                _path.clear();
                _path.assign((MAP_HEIGHT + 3) * MAP_WIDTH, 0);
                if (findPacman(pos.getY(), pos.getX(),
                               0, _pac.getCurrentPos()) != 0) {
                        _compute = 0;
                        std::cerr << "can not find pacman" << std::endl;
                        return false;
                }
        }
        if (_oldPath != 0)
                _map[_currentPos] = _oldPath;
        _map[_currentPos] = _oldPath;
        std::cerr << "changing pos of ghost from " << getCoords(_currentPos).getY() << ", " << getCoords(_currentPos).getX() << " to " <<
                                                getCoords(_path[_compute + 1]).getY() << ", " << getCoords(_path[_compute + 1]).getX() << std::endl;
        _currentPos = _path[++_compute];
        _oldPath = _map[_currentPos];
        _map[_currentPos] = 'G';
        if (_compute == COMPUTE) {
                _oldPath = 0;
                _compute = 0;
        }
        return true;
}

bool Arcade::Ghost::isTimeToMove()
{
        auto time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(time - _time).count();

        return duration >= BEGIN_MOVE;
}

Arcade::Vect<size_t> Arcade::Ghost::getCoords(size_t pos) const
{
        return {pos % (MAP_WIDTH), pos / (MAP_HEIGHT)};
}

size_t Arcade::Ghost::getIndex(size_t y, size_t x, int yOff, int xOff) const
{
        if (yOff == 0 && xOff == 0)
                return y * MAP_WIDTH + x;
        if (yOff != 0 && xOff == 0)
                return (y + yOff) * MAP_WIDTH + x;
        if (yOff == 0 && xOff != 0)
                return y * MAP_WIDTH + (x + xOff);
        if (yOff != 0 && xOff != 0)
                return (y * yOff) * MAP_WIDTH + (x + xOff);
        return 0;
}

bool Arcade::Ghost::closeToTarget(size_t y, size_t x, size_t target)
{
        return getIndex(y, x, 1, 0) == target ||
               getIndex(y, x, -1, 0) == target ||
               getIndex(y, x, 0, 1) == target ||
                getIndex(y, x, 0, -1) == target;
}

int Arcade::Ghost::findPacman(size_t y, size_t x, size_t i,
                              size_t target)
{
        //print_map(_tmp);
        std::cerr << "i = " << i << std::endl;
        _path[i] = getIndex(y, x, 0, 0);
        _tmp[getIndex(y, x, 0, 0)] = 'o';
        if (closeToTarget(y, x, target))
                return (0);
        if (y + 1 < MAP_HEIGHT + 3 && _tmp[getIndex(y, x, 1, 0)] == ' ')
                return (findPacman(++y, x, ++i, target));
        else if (y > 0 && _tmp[getIndex(y, x, -1, 0)] == ' ')
                return (findPacman(--y, x, ++i, target));
        else if (x < MAP_WIDTH && _tmp[getIndex(y, x, 0, 1)] == ' ')
                return (findPacman(y, ++x, ++i, target));
        else if (x > 0 && _tmp[getIndex(y, x, 0, -1)] == ' ')
                return (findPacman(y, --x, ++i, target));
        else
                return (backtrack(y, x, i, target));
}

int Arcade::Ghost::backtrack(size_t y, size_t x, size_t i,
                             size_t target)
{
        size_t new_k;

        new_k = i - 1;
        //print_map(_tmp);
        if (_tmp[0] == '.' &&
            (y + 1 < MAP_HEIGHT + 3 &&
             _tmp[getIndex(y, x, 1, 0)] == ' ') &&
            (y > 0 && _tmp[getIndex(y, x, -1, 0)] == ' ') &&
            (x < MAP_WIDTH && _tmp[getIndex(y, x, 0, 1)] == ' ') &&
            (x > 0 && _tmp[getIndex(y, x, 0, -1)] == ' '))
                return (84);
        if ((y + 1 < MAP_HEIGHT + 3 &&
             _tmp[getIndex(y, x, 1, 0)] == ' ') ||
            (y > 0 && _tmp[getIndex(y, x, -1, 0)] == ' ') ||
            (x < MAP_WIDTH && _tmp[getIndex(y, x, 0, 1)] == ' ') ||
            (x > 0 && _tmp[getIndex(y, x, 0, -1)] == ' '))
                return (findPacman(y, x, i, target));
        return (backtrack(getCoords(_path[i]).getY(), getCoords(_path[i]).getX(),
                          new_k, target));
}

const std::string &Arcade::Ghost::getName() const
{
        return _name;
}

