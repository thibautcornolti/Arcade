/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include "../shared_header/IGameLib.hpp"

namespace Arcade {
	class TestGameLib : public Arcade::IGameLib {
	public:
		TestGameLib();
		~TestGameLib();

		const std::string &getName() const final;
		bool init() final;
		bool stop() final;
		bool open() final;
		bool close() final;
		void applyEvent(Keys) final;
		void update() final;
		void refresh(IGraphicLib *) final;
	protected:
	private:
		std::string _name = "Test";
		Arcade::TextBox _title;
		Arcade::PixelBox _map;
		Arcade::Vect<size_t> _player;
	};
}
