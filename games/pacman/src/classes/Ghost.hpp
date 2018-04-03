/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Ghost.h
*/

#ifndef CPP_ARCADE_GHOST_H
#define CPP_ARCADE_GHOST_H

#define MAP_WIDTH 28
#define MAP_HEIGHT 28

namespace Arcade {
    class Ghost {
    public:
        Ghost();
        ~Ghost();
        enum MOVE {
            RIGHT = 1,
            LEFT = -1,
            TOP = -(MAP_HEIGHT),
            BOT = (MAP_HEIGHT),
            STILL = 0
        };
    };
}

#endif /* !CPP_ARCADE_GHOST_H */
