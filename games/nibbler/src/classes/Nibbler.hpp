/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <chrono>
#include <list>
#include <map>
#include "../shared_header/IGameLib.hpp"
#include "../shared_header/Scoreboard.hpp"
#include "../shared_header/Scale.hpp"

#define ASSETS_PATH	"assets/nibbler/maps/map"
#define MAP		25

namespace Arcade {
	class Nibbler : public Arcade::IGameLib {
	public:
		Nibbler();
		~Nibbler();

		const std::string getName() const final;
		std::string getPlayerName() const;
		bool init() final;
		bool stop() final;
		bool applyEvent(Keys) final;
		bool update() final;
		void refresh(IGraphicLib &) final;
		size_t getScore() final;

		enum STATUS {
			RUNNING,
			PAUSED,
			CHEAT,
			WAITING,
			ENDED
		};

		enum MOVE {
			RIGHT = 1,
			LEFT = -1,
			TOP = -(MAP + 2),
			BOT = (MAP + 2)
		};

		Arcade::Vect<size_t> getCoords(size_t) const;
		void updatePixel(Arcade::PixelBox&);
		void display(IGraphicLib &);
		std::string getStatus() const;
		void displayGameInfo(IGraphicLib &);
		void initMap();

		void gameOver(IGraphicLib &);
		bool isTimeToMove();
		bool restart();
		bool food();
		bool collide(size_t&);
		void addLink();
		void addFood();
		void setMove(MOVE);
		bool move();

	private:
		typedef struct s_nibbler {
			size_t currentPos;
			size_t lastPos;
		} t_nibbler;

	private:
		Scoreboard *_score;
		Scale *_scale;

		std::chrono::time_point<std::chrono::high_resolution_clock> _time;
		std::chrono::time_point<std::chrono::high_resolution_clock> _gameOver;
		std::string _name = "Nibbler";
		std::string _playerName = "Unknown";
		std::string _map;
		size_t _gameOverTimer = 10;
		double _speed = 150.0;
		std::list<t_nibbler> _nibbler;
		MOVE _current = RIGHT;
		STATUS _game = RUNNING;
	};
}
