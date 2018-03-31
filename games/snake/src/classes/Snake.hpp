/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include "../shared_header/IGameLib.hpp"

#define MAP	25
#define SPEED	300

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

		enum Move {
			RIGHT,
			LEFT,
			TOP,
			BOT
		};

		void display();
		bool move(Move);

	private:
		std::string _name = "Snake";
		Move _current = RIGHT;
		Arcade::TextBox _title;
		Arcade::PixelBox _map;
		Arcade::Vect<size_t> _player;
	};
}
