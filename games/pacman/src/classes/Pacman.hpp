/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman.h
*/

#ifndef CPP_ARCADE_PACMAN_H
#define CPP_ARCADE_PACMAN_H

#include <iostream>
#include <fstream>
#include "PacPlayer.hpp"
#include "Ghost.hpp"
#include "../shared_header/IGameLib.hpp"
#include "../../../shared_classes/Scoreboard.hpp"
#include "../../../shared_classes/Scale.hpp"


#define MAP_WIDTH 28
#define MAP_HEIGHT 28
#define ASSETS_PATH "games/pacman/assets/map.txt"

namespace Arcade {
    class Pacman : public Arcade::IGameLib {
    public:
        Pacman();
        ~Pacman();

        const std::string getName() const final;
        bool init() final;
        bool stop() final;
        bool open() final;
        bool close() final;
        void applyEvent(Keys) final;
        void update() final;
        void setPlayerName(const std::string &name) final;
        void refresh(IGraphicLib &) final;
        bool restart();
        bool readMap();
        std::string getStatus() const;
        void display(IGraphicLib &);
        void displayGameInfo(IGraphicLib &);
        void updatePixel();
        void move();
        size_t findPlayer();
        Arcade::Vect<size_t> getCoords(size_t) const;

        enum STATUS {
            INIT,
            RUNNING,
            PAUSED,
            ENDED
        };
        enum MOVE {
            RIGHT = 1,
            LEFT = -1,
            TOP = -(MAP_HEIGHT),
            BOT = (MAP_HEIGHT),
            STILL = 0
        };

    private:
        std::string _name = "Pacman";
        std::string _playerName = "Unknown";
        std::string _map;
        Scoreboard *_score;
        Scale *_scale;
        MOVE _move = STILL;
        size_t _current_pos;
        size_t _initial_pos;
        bool _init = false;
        STATUS _status = INIT;
        Arcade::PacPlayer _player;
        std::vector<Arcade::Ghost> _ghosts;
        Arcade::PixelBox _pixelMap;
    };
}



#endif /* !CPP_ARCADE_PACMAN_H */
