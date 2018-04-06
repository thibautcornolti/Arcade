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
		bool init() final;
		bool stop() final;
		bool applyEvent(Keys) final;
		bool update() final;
		void refresh(IGraphicLib &) final;
		size_t getScore() final;
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
