/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "TestGameLib.hpp"

Arcade::TestGameLib::TestGameLib()
	: _title("", Arcade::Vect<size_t>())
	, _map()
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
	_player = Vect<size_t>();
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

void Arcade::TestGameLib::applyEvent(Arcade::Keys key)
{
	switch (key) {
		case Arcade::Keys::Z:
			if (_player.getY() > 0)
				_player.setY(_player.getY() - 1);
			break ;
		case Arcade::Keys::S:
			if (_player.getY() < _map.getHeight() - 1)
				_player.setY(_player.getY() + 1);
			break ;
		case Arcade::Keys::D:
			if (_player.getX() < _map.getWidth() - 1)
				_player.setX(_player.getX() + 1);
			break ;
		case Arcade::Keys::Q:
			if (_player.getX() > 0)
				_player.setX(_player.getX() - 1);
			break ;
		default:
			break ;
	}
}

void Arcade::TestGameLib::update()
{
	auto size = Arcade::Vect<size_t>(30, 15);
	auto pos = Arcade::Vect<size_t>(2, 1);
	_map = Arcade::PixelBox(size, pos);
	_map.putPixel(_player, Arcade::Color(255));
	pos.setXY(0, 18);
	_title = Arcade::TextBox("best game ever\n\
use ZQSD to move\n\
echap = return to lobby\n\
tu peu revenir et le player sera la ou tu la laisser",
		pos, 30UL, Arcade::Color(255));
}

void Arcade::TestGameLib::refresh(IGraphicLib *lib)
{
	lib->clearWindow();
	
	lib->drawPixelBox(_map);
	lib->drawText(_title);
	lib->refreshWindow();
}
