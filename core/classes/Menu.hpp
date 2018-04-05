/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Manu.hpp
*/

#ifndef PROJECT_MENU_HPP
#define PROJECT_MENU_HPP

#include <vector>
#include <functional>
#include <map>
#include <string>
#include "Core.hpp"
#include "../../games/shared_classes/Scoreboard.hpp"
#include "../../games/shared_classes/Scale.hpp"
#include "../shared_header/IGraphicLib.hpp"
#include "../shared_header/TextBox.hpp"
#include "../shared_header/PixelBox.hpp"

namespace Arcade {

	class Menu {
	public:
		Menu(std::vector<std::string> &);
		~Menu() = default;

		void applyEvent(Arcade::Keys, Core &);
		void refresh(Arcade::IGraphicLib &);
		void addLetter(char letter = 'A');
		void activeCaps();
		void removeLetter();
		void resetPlayer();
		void selector(Arcade::IGraphicLib&);
		void displayScoreboard(Arcade::IGraphicLib&);

	private:
		Scoreboard *_score;
		Scale *_scale;

		std::vector<std::string> _games;
		std::string _playerName;
		size_t _selection = 0;

		std::map<const Arcade::Keys, std::function<void()>> _keyboard;
		bool _capsActive = false;
	};
}


#endif /* !PROJECT_MENU_HPP */
