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

		const std::string getName() const final;
		void setPlayerName(const std::string &) final;
		bool init() final;
		bool stop() final;
		bool open() final;
		bool close() final;
		void applyEvent(Keys) final;
		void update() final;
		void refresh(IGraphicLib &) final;
	protected:
	private:
		std::string _name = "Test";
		size_t _height = 10;
		size_t _width = 15;
		Arcade::TextBox _title;
		Arcade::PixelBox _pixelBox;
		Arcade::Vect<size_t> _player;
	};
}
