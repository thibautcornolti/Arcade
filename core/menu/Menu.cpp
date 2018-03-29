/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Manu.cpp
*/

#include "Menu.hpp"
#include <unistd.h>

Menu::Menu(Core &core, int width, int height) :_core(core),
                                               _selector(0),
                                               _record_lenght(2)
{

}

Menu::~Menu() {}

void Menu::initMenu()
{
	_running = true;
	auto height = (size_t)_core._getGraph().getMaxY();
	auto width = (size_t)_core._getGraph().getMaxX();
	Arcade::Vect<size_t> pos = {10, 5};
	size_t center = width / 2;

	_text.push_back(Arcade::TextBox("Menu", {center - 2, height / 5 * 2}, 1, 0, 0));
	_text.push_back(Arcade::TextBox("Play", {center - 2, height / 5 * 3}, 1, 0, 0));
	_text.push_back(Arcade::TextBox("Library", {center - 3, height / 5 * 4}, 1, 0, 0));
}

void Menu::add_selector(size_t i)
{
	auto txt = _text[i].getValue();
	txt.insert(txt.begin(), '<');
	txt.insert(txt.end(), '>');
	_text[i].setValue(txt);
}

void Menu::clear_selector(size_t i)
{
	auto txt = _text[i].getValue();
	txt.erase(txt.begin());
	txt.erase(txt.end() - 1);
	_text[i].setValue(txt);
}

void Menu::displayMenu()
{
	Arcade::Keys key = Arcade::Keys::NONE;

	for (size_t i = 0; i < _text.size(); i++) {
		_core._getGraph().pollEvents();
		key = _core._getGraph().getLastEvent();
		_core._getGraph().clearEvents();
		if (key == Arcade::Keys::UP && _selector > 0) {
			_selector--;
		} else if (key == Arcade::Keys::DOWN &&
			_selector < _record_lenght)
			_selector++;
		if (_selector == i)
			add_selector(i);
		_core._getGraph().drawText(_text[i]);
		if (_selector == i)
			clear_selector(i);
	}
}

void Menu::run()
{
	if (!_running)
		initMenu();
	_core._getGraph().clearWindow();
	displayMenu();
	_core._getGraph().refreshWindow();
}