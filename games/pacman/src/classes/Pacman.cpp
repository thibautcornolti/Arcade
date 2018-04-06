/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman.cpp
*/

#include <sstream>
#include <algorithm>
#include <unistd.h>
#include "Pacman.hpp"

Arcade::Pacman::Pacman()
{
        _score = new Scoreboard();
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
        std::cerr << "INIT PACMAN" << std::endl;
        _player = PacPlayer();
        _ghosts.assign(4, Ghost());
        if (!readMap())
                return false;
        _current_pos = findPlayer();
        if (_current_pos == UINT32_MAX) {
                std::cerr << "Can not find initial player position in map" << std::endl;
                return false;
        }
        _initial_pos = _current_pos;
        return true;
}

bool Arcade::Pacman::stop()
{
        return true;
}

bool Arcade::Pacman::restart()
{
        return true;
}

bool Arcade::Pacman::applyEvent(Arcade::Keys key)
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
                        _status = (_status == PAUSED) ? RUNNING : PAUSED;
                        break;
                case Arcade::Keys::R:
                        restart();
                        break;
                case Arcade::Keys::G:
                        _godmode = !_godmode;
                        break;
                default:
                        _move = Arcade::Pacman::MOVE::STILL;
                        break;
        }
        return true;
}

bool Arcade::Pacman::update()
{
     return true;
}

void Arcade::Pacman::refresh(IGraphicLib &lib)
{
        _pixelMap = Arcade::PixelBox({MAP_WIDTH, MAP_HEIGHT + 3},
                                     {lib.getMaxX() / 2 - MAP_WIDTH / 2,
                                      lib.getMaxY() / 2 - MAP_HEIGHT / 2});
        if (!_init) {
                _init = true;
                _status = Arcade::Pacman::STATUS::RUNNING;
        }
        if (_status == Arcade::Pacman::STATUS::RUNNING &&
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
        linkDoors();
        return true;
}

Arcade::Vect<size_t> Arcade::Pacman::getCoords(size_t pos) const
{
        return {pos % (MAP_WIDTH), pos / (MAP_HEIGHT)};
}

std::string Arcade::Pacman::getStatus() const
{
        switch (_status) {
                case RUNNING:
                        return "Running";
                case PAUSED:
                        return "Paused";
                default:
                        return "Ended";
        }
}

void Arcade::Pacman::display(Arcade::IGraphicLib &lib)
{
        updatePixel();
        _scale->setCentering(Scale::BOTH);
        _scale->setWindowSize({lib.getMaxX(), lib.getMaxY()});
        _scale->scalePixelBox({50, 50}, {50, 50}, _pixelMap);
        displayGameInfo(lib);
        lib.drawPixelBox(_pixelMap);
}

void Arcade::Pacman::displayGameInfo(IGraphicLib &lib)
{
        Arcade::TextBox title("Pacman", {(lib.getMaxX() - 5) / 2, 5}, 20);
        Arcade::TextBox statut("Statut: ", {(lib.getMaxX() - 5) / 2, 7}, 20);
        Arcade::TextBox score("Score: ", {(lib.getMaxX() - 5) / 2, 8}, 20);
        Arcade::TextBox scoreb("Scoreboard", {(lib.getMaxX()) / 3 * 2 + 10, 7}, 20);
        Arcade::TextBox godmode("God Mode: ", {(lib.getMaxX()) / 3 * 2 + 10, 10}, 20);

        statut.setValue(statut.getValue() + getStatus());
        statut.setX((lib.getMaxX() - statut.getValue().size()) / 2);
        score.setValue(score.getValue() + std::to_string(_score->getScores()));
        score.setX((lib.getMaxX() - score.getValue().size()) / 2);
        if (_godmode)
                godmode.setValue(godmode.getValue() + "enable");
        else
                godmode.setValue(godmode.getValue() + "disable");
        lib.drawText(title);
        lib.drawText(statut);
        lib.drawText(score);
        lib.drawText(scoreb);
        lib.drawText(godmode);
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
                                if (_godmode)
                                        _pixelMap.putPixel(getCoords(i),
                                                           {255, 102, 0, 255});
                                else
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

void Arcade::Pacman::useLink()
{
        for (size_t i = 0; i < _link.size(); ++i) {
                if (getCoords(_current_pos + _move) == _link[i].first) {
                        _current_pos = _link[i].second.getY() * MAP_WIDTH + _link[i].second.getX();
                        break;
                } else if (getCoords(_current_pos + _move) == _link[i].second) {
                        _current_pos = _link[i].first.getY() * MAP_WIDTH + _link[i].first.getX();
                        break;
                }
        }
        if (_map[_current_pos + TOP] != '#' &&
            _map[_current_pos + TOP] != '|' &&
            _map[_current_pos + TOP] != '\'')
                _current_pos += TOP;
        else if (_map[_current_pos + BOT] != '#' &&
                 _map[_current_pos + BOT] != '|' &&
                 _map[_current_pos + BOT] != '\'')
                _current_pos += BOT;
        else if (_map[_current_pos + LEFT] != '#' &&
                 _map[_current_pos + LEFT] != '|' &&
                 _map[_current_pos + LEFT] != '\'')
                _current_pos += LEFT;
        else if (_map[_current_pos + RIGHT] != '#' &&
                 _map[_current_pos + RIGHT] != '|' &&
                 _map[_current_pos + RIGHT] != '\'')
                _current_pos += RIGHT;
}

void *Arcade::Pacman::godTime(void *ptr)
{
        auto *god = (bool *) ptr;
        sleep(GODTIME);
        (*god) = false;
        return NULL;
}

void Arcade::Pacman::move()
{
        if (_map[_current_pos + _move] == '#') {
                _move = Arcade::Pacman::MOVE::STILL;
                return;
        }
        if (_map[_current_pos + _move] == '.')
                _score->addScores(10);
        if (_map[_current_pos + _move] == '*') {
                _godmode = true;
                pthread_create(&_id, NULL, &(Arcade::Pacman::godTime), &_godmode);
        }
        _map[_current_pos] = ' ';
        if (_map[_current_pos + _move] == '|')
                useLink();
        else
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

bool Arcade::Pacman::linkDoors()
{
        Vect<size_t> pos;
        for (size_t i = 0; i < _map.size(); ++i) {
                if (_map[i] == '|') {
                        pos = getCoords(i);
                        for (int j = 1; j + pos.getX() < MAP_WIDTH; ++j) {
                                if (_map[pos.getY() * MAP_WIDTH + j + pos.getX()] == '|')
                                        _link.push_back({pos, getCoords(pos.getY() * MAP_WIDTH + j + pos.getX())});
                        }
                }
        }
        return true;
}

size_t Arcade::Pacman::getScore()
{
        return _score->getScores();
}

//TODO make the ghost class
//TODO chase and flee ia
//TODO kill and win condition
//TODO ghost replacement when killed by god mode
