/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <list>
#include "../shared_header/IGameLib.hpp"

#define MAP	25
#define SPEED	150

namespace Arcade {
	class Snake : public Arcade::IGameLib {
	public:
		Snake();
		~Snake();

		const std::string &getName() const final;
		bool init() final;
		bool stop() final;
		bool open() final;
		bool close() final;
		void applyEvent(Keys) final;
		void update() final;
		void refresh(IGraphicLib *) final;

		enum STATUS {
			RUNNING,
			PAUSED,
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
		void display(IGraphicLib *);
		std::string getStatus() const;
		void displayGameInfo(IGraphicLib *);

		bool restart();
		bool collide();
		void addLink();
		void addFood();
		void setMove(MOVE);
		bool move();

	private:
		typedef struct s_snake {
			int id;
			size_t currentPos;
			size_t lastPos;
		} t_snake;

	private:
		std::string _name = "Snake";
		std::string _map;
		std::list<t_snake> _snake;
		MOVE _current = RIGHT;
		STATUS _game = RUNNING;
	};
}
