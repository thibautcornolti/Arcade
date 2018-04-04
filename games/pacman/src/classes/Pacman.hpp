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
        bool readMap();
        void display(IGraphicLib &);
        void updatePixel();
        Arcade::Vect<size_t> getCoords(size_t) const;

        enum STATUS {
            RUNING,
            PAUSED,
            ENDED
        };

    private:
        std::string _name = "Pacman";
        std::string _map;
        bool _init = false;
        Arcade::PacPlayer _player;
        std::vector<Arcade::Ghost> _ghosts;
        Arcade::PixelBox _pixelMap;
    };
}



#endif /* !CPP_ARCADE_PACMAN_H */
