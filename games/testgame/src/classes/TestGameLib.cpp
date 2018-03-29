/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "TestGameLib.hpp"

Arcade::TestGameLib::TestGameLib()
{
}

Arcade::TestGameLib::~TestGameLib()
{
}

const std::string &Arcade::TestGameLib::getName() const
{
	return _name;
}

bool Arcade::TestGameLib::init()
{
	return true;
}

bool Arcade::TestGameLib::stop()
{
	return true;
}

bool Arcade::TestGameLib::open()
{
	return true;
}

bool Arcade::TestGameLib::close()
{
	return true;
}

bool Arcade::TestGameLib::loop(IGraphicLib *lib)
{
	auto s = Arcade::Vect<size_t>(10, 10);
	auto a = Arcade::PixelBox(s, s);
	a.putPixel(Arcade::Vect<size_t>(4, 0), Arcade::Color(0, 0, 0, 1));
	auto b = Arcade::TextBox("salut", 0, 0, 15, 10);
	lib->drawPixelBox(a);
	lib->drawText(b);
	lib->refreshWindow();
	return lib->isOpen();
}
