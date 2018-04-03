/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** PacPlayer.h
*/

#ifndef CPP_ARCADE_PACPLAYER_H
#define CPP_ARCADE_PACPLAYER_H

#define MAP_WIDTH 28
#define MAP_HEIGHT 31

namespace Arcade {
    class PacPlayer {
    public:
        PacPlayer();
        ~PacPlayer();
        enum MOVE {
            RIGHT = 1,
            LEFT = -1,
            TOP = -(MAP_HEIGHT),
            BOT = (MAP_HEIGHT),
            STILL = 0
        };
    };
}

#endif /* !CPP_ARCADE_PACPLAYER_H */
