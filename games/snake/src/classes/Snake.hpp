/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <list>
#include "../shared_header/IGameLib.hpp"

#define MAP	40
#define SPEED	500000

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
			RIGHT,
			LEFT,
			TOP,
			BOT
		};

		Arcade::Vect<size_t> getCoords(size_t) const;
		void updatePixel(Arcade::PixelBox&);
		void display(IGraphicLib *);

		void addFood();
		bool move(MOVE);

	private:
		typedef struct s_snake {
			size_t pos;
			Arcade::Vect<size_t> coord;
		} t_snake;

	private:
		std::string _name = "Snake";
		std::string _map;
		std::list<t_snake> _snake;
		MOVE _current = RIGHT;
		STATUS _game = ENDED;
	};
}
