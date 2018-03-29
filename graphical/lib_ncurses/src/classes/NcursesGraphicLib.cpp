/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "NcursesGraphicLib.hpp"

Arcade::NcursesGraphicLib::NcursesGraphicLib()
{}

Arcade::NcursesGraphicLib::~NcursesGraphicLib()
{}

std::string Arcade::NcursesGraphicLib::getName() const
{
	return "NCurses";
}

bool Arcade::NcursesGraphicLib::isOpen() const
{
	return _isRendering;
}

bool Arcade::NcursesGraphicLib::initRenderer()
{
	return true;
}

bool Arcade::NcursesGraphicLib::stopRenderer()
{
	return true;
}

void Arcade::NcursesGraphicLib::clearWindow()
{
	clear();
}

bool Arcade::NcursesGraphicLib::openRendering()
{
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	timeout(0);
	_isRendering = true;
	return true;
}

bool Arcade::NcursesGraphicLib::closeRendering()
{
	endwin();
	_isRendering = false;
	return true;
}

void Arcade::NcursesGraphicLib::refreshWindow()
{
	refresh();
}

void Arcade::NcursesGraphicLib::drawPixelBox(PixelBox &pixelBox)
{
	size_t x = pixelBox.getX();
	size_t y = pixelBox.getY();
	for (size_t xi = 0 ; xi < pixelBox.getWidth() ; ++xi)
		for (size_t yi = 0 ; yi < pixelBox.getHeight() ; ++yi) {
			Arcade::Color c = pixelBox.getPixel(Vect<size_t>(yi, xi));
			mvprintw(yi + y, xi + x, "%d", c.getAlpha());
		}
}

void Arcade::NcursesGraphicLib::drawText(TextBox &textBox)
{
	mvprintw(textBox.getPosH(), textBox.getPosW(),
		textBox.getValue().c_str());
}

Arcade::Keys Arcade::NcursesGraphicLib::getLastEvent()
{
	return _lastEvent;
}

bool Arcade::NcursesGraphicLib::pollEvent()
{
	if (_isRendering == false)
		return false;
	auto k = getch();

	for (size_t i = 0 ; i < _keymap.size() ; ++i) {
		if (k == _keymap[i].first) {
			_lastEvent = _keymap[i].second;
			break ;
		}
	}
	return true;
}

void Arcade::NcursesGraphicLib::cleanEvent()
{
	_lastEvent = Arcade::Keys::NONE;
}

Arcade::Vect<size_t> Arcade::NcursesGraphicLib::getScreenSize() const 
{
	return Arcade::Vect<size_t>(getMaxX(), getMaxY());
}

int Arcade::NcursesGraphicLib::getMaxY() const
{
	return LINES;
}

int Arcade::NcursesGraphicLib::getMaxX() const
{
	return COLS;
}
