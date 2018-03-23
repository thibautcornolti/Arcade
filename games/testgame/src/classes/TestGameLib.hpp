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
		bool initGame() final;
		bool stopGame() final;
		bool openGame() final;
		bool closeGame() final;
		bool loop(IGraphicLib *graphicsLib) final;
	protected:
	private:
		std::string _name = "Test";
	};
}
