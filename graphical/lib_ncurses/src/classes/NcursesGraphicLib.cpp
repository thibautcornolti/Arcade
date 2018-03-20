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

std::string Arcade::NcursesGraphicLib::getName()
{
	return "NCurses";
}

bool Arcade::NcursesGraphicLib::supportSprite() const
{
	return false;
}

bool Arcade::NcursesGraphicLib::supportSound() const
{
	return false;
}

bool Arcade::NcursesGraphicLib::needFont() const
{
	return false;
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

void Arcade::NcursesGraphicLib::drawPixelBox(PixelBox *pixelBox)
{
	size_t posH = pixelBox->getPosH();
	size_t posW = pixelBox->getPosW();
	for (size_t h = posH ; h < pixelBox->getH() + posH ; ++h)
		for (size_t w = posW ; w < pixelBox->getW() + posW ; ++w)
			mvprintw(h, w, "*");
}

void Arcade::NcursesGraphicLib::drawText(TextBox *textBox)
{
	mvprintw(textBox->getPosH(), textBox->getPosW(),
		textBox->getValue().c_str());
}

void Arcade::NcursesGraphicLib::playSound(void *)
{}

void Arcade::NcursesGraphicLib::pauseSound(void *)
{}

void Arcade::NcursesGraphicLib::stopSound(void *)
{}

void *Arcade::NcursesGraphicLib::loadTextFont(std::string)
{
	return nullptr;
}

void *Arcade::NcursesGraphicLib::loadSprite(std::string)
{
	return nullptr;
}

void *Arcade::NcursesGraphicLib::loadSound(std::string)
{
	return nullptr;
}

Arcade::Keys Arcade::NcursesGraphicLib::getLastEvent()
{
	auto temp = _lastEvent;
	_lastEvent = Arcade::Keys::NONE;
	return temp;
}

bool Arcade::NcursesGraphicLib::pollEvent()
{
	if (_isRendering == false)
		return false;
	int keys[] = {
		KEY_RIGHT, KEY_LEFT, 27,
	};
	Arcade::Keys match[] = {
		Arcade::Keys::RIGHT,
		Arcade::Keys::LEFT,
		Arcade::Keys::ESC,
	};
	auto k = getch();
	for (size_t i = 0 ; i < 3 ; ++i)
		if (k == keys[i]) {
			_lastEvent = match[i];
			break ;
		}
	return true;
}

void Arcade::NcursesGraphicLib::cleanEvent()
{}

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
