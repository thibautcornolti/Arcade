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

#define ASSETS_PATH	"games/snake/src/assets/map"
#define ASSETS_TITLE	"games/snake/src/assets/title"
#define MAP		25
#define SPEED		150.0

namespace Arcade {
	class Snake : public Arcade::IGameLib {
	public:
		Snake();
		~Snake();

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
			ENDED
		};

		enum MOVE {
			RIGHT = 1,
			LEFT = -1,
			TOP = -(MAP + 2),
			BOT = (MAP + 2)
		};

		Arcade::Vect<size_t> getCoords(size_t) const;
		void updatePixel(Arcade::PixelBox &);
		void display(IGraphicLib &);
		std::string getStatus() const;
		void displayGameInfo(IGraphicLib &);
		bool isTimeToMove();

		bool restart();
		bool food();
		bool collide(size_t&);
		void addLink();
		void addFood();
		void setMove(MOVE);
		bool move();

	private:
		typedef struct s_snake {
			size_t currentPos;
			size_t lastPos;
		} t_snake;

	private:
		Scoreboard *_score;
		Scale *_scale;

		std::chrono::time_point<std::chrono::high_resolution_clock> _time;
		std::string _name = "Snake";
		std::string _playerName = "Unknown";
		std::string _map;
		std::list<t_snake> _snake;
		MOVE _current = RIGHT;
		STATUS _game = RUNNING;
	};
}
