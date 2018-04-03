/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Manu.hpp
*/

#ifndef PROJECT_MENU_HPP
#define PROJECT_MENU_HPP

#include <vector>
#include "../shared_header/IGraphicLib.hpp"
#include "../shared_header/TextBox.hpp"

class Menu {
public:
	Menu(std::vector<std::string> &);
	~Menu() = default;

	void applyEvent(Arcade::Keys, Core &);
	void refresh(Arcade::IGraphicLib &);

private:
	void _genMenu(Arcade::IGraphicLib &);
	void _addSelector(size_t);
	void _clearSelector(size_t);

private:
	std::vector<Arcade::TextBox> _text;
	std::vector<std::string> _games;
	size_t _selector = 0;
};


#endif /* !PROJECT_MENU_HPP */
