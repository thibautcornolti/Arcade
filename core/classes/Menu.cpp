/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Manu.cpp
*/

#include "Core.hpp"
#include "Menu.hpp"
#include <unistd.h>

Menu::Menu(std::vector<std::string> &games)
	: _text()
	, _games(games)
{}

void Menu::_genMenu(Arcade::IGraphicLib *graph)
{
	auto height = graph->getMaxY();
	auto width = graph->getMaxX();

	_text.clear();
	for (size_t i = 0 ; i < _games.size() ; ++i) {
		auto pos = Arcade::Vect<size_t>(
			width / 2 - _games[i].length(),
			(height / (_games.size() + 1)) * (i + 1)
		);
		auto fontSize = 30UL;
		auto color = Arcade::Color(255, 255, 255, 255);
		auto t = Arcade::TextBox(_games[i], pos, fontSize, color);
		_text.push_back(t);
	}
}

void Menu::_addSelector(size_t i)
{
	auto txt = _text[i].getValue();
	txt.insert(txt.begin(), '<');
	txt.insert(txt.end(), '>');
	_text[i].setValue(txt);
	_text[i].setX(_text[i].getX()-1);
}

void Menu::_clearSelector(size_t i)
{
	auto txt = _text[i].getValue();
	txt.erase(txt.begin());
	txt.erase(txt.end() - 1);
	_text[i].setValue(txt);
	_text[i].setX(_text[i].getX()+1);
}

void Menu::applyEvent(Arcade::Keys key, Core &core)
{
	if (key == Arcade::Keys::UP && _selector > 0) {
			_selector--;
	} else if (key == Arcade::Keys::DOWN &&
			_selector < _text.size() - 1)
			_selector++;
	else if (key == Arcade::Keys::ENTER) {
		core.openGame(_selector);
	}
}

void Menu::refresh(Arcade::IGraphicLib *graph)
{
	_genMenu(graph);
	graph->clearWindow();
	for (size_t i = 0; i < _text.size(); i++) {
		if (_selector == i)
			_addSelector(i);
		graph->drawText(_text[i]);
		if (_selector == i)
			_clearSelector(i);
	}
	graph->refreshWindow();
}
