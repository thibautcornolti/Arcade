/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Manu.hpp
*/

#ifndef PROJECT_MENU_HPP
#define PROJECT_MENU_HPP

#include <vector>
#include "../classes/Core.hpp"

class Menu {
public:
	Menu(Core&, int, int);
	~Menu();

	void run();

private:
	void initMenu();
	void displayMenu();
	void add_selector(size_t);
	void clear_selector(size_t);

private:
	Core &_core;
	std::vector<Arcade::TextBox> _text;
	bool _running = false;
	size_t _selector;
	size_t _record_lenght;
};


#endif /* !PROJECT_MENU_HPP */
