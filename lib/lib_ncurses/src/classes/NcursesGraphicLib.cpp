/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "NcursesGraphicLib.hpp"

Arcade::NcursesGraphicLib::NcursesGraphicLib()
{
}

Arcade::NcursesGraphicLib::~NcursesGraphicLib()
{
}

bool Arcade::NcursesGraphicLib::isOpen() const
{
	return _isRendering;
}

bool Arcade::NcursesGraphicLib::initRenderer()
{
}

bool Arcade::NcursesGraphicLib::stopRenderer()
{
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
	_isRendering = true;
	return true;
}

bool Arcade::NcursesGraphicLib::closeRendering()
{
	endwin();
	_isRendering = false;
	return true;
}

void Arcade::NcursesGraphicLib::drawPixelBox(PixelBox *pixelBox)
{

}

Arcade::Vect<size_t> Arcade::NcursesGraphicLib::getScreenSize() const 
{
	return Arcade::Vect<size_t>(COLS, LINES);
}

int Arcade::NcursesGraphicLib::getMaxY() const
{
	return LINES;
}

int Arcade::NcursesGraphicLib::getMaxX() const
{
	return COLS;
}
