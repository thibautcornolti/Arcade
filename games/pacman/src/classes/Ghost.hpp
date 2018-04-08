/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Ghost.h
*/

#ifndef CPP_ARCADE_GHOST_H
#define CPP_ARCADE_GHOST_H

#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include "../shared_header/IGameLib.hpp"
#include "Pacman.hpp"

#define COMPUTE 5
#define BEGIN_MOVE 100
#define MAP_WIDTH 28
#define MAP_HEIGHT 28

namespace Arcade {
        class Pacman;
}

namespace Arcade {
        class Ghost {
        public:
                Ghost(std::string &, const std::string &, Arcade::Pacman &);
                ~Ghost();
                bool placeGhost();
                bool move();
                bool isTimeToMove();
                Arcade::Vect<size_t> getCoords(size_t) const;
                size_t getIndex(size_t, size_t, int, int) const;
                int findPacman(size_t, size_t, size_t, size_t);
                int backtrack(size_t, size_t, size_t, size_t);
                bool closeToTarget(size_t y, size_t x, size_t target);
                const std::string &getName() const;
                void updateGhost();
                enum MOVE {
                        RIGHT = 1,
                        LEFT = -1,
                        TOP = -(MAP_HEIGHT),
                        BOT = (MAP_HEIGHT),
                        STILL = 0
                };
        private:
                std::string &_map;
                const std::string &_name;
                std::string _tmp;
                Arcade::Pacman &_pac;
                std::vector<size_t> _path;
                std::chrono::time_point<std::chrono::high_resolution_clock> _time;
                size_t _initialPos;
                size_t _currentPos;
                char _oldPath = 0;
                size_t _compute = 0;
                MOVE _move = STILL;
                static bool _canMove;
        };
}

#endif /* !CPP_ARCADE_GHOST_H */
