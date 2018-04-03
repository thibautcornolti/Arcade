/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "TestGameLib.hpp"

Arcade::TestGameLib::TestGameLib()
	: _title("", Arcade::Vect<size_t>())
	, _pixelBox()
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
			if (_player.getY() < _height - 1)
				_player.setY(_player.getY() + 1);
			break ;
		case Arcade::Keys::D:
			if (_player.getX() < _width - 1)
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
	auto pos = Arcade::Vect<size_t>(0, 0);
	_title = Arcade::TextBox("best game ever\n\
use ZQSD to move\n\
echap = return to lobby\n\
tu peu revenir et le player sera la ou tu la laisser",
		pos, 30UL, Arcade::Color(255, 0, 0, 255));
}

void Arcade::TestGameLib::refresh(IGraphicLib *lib)
{
	lib->clearWindow();
	
	auto size = Arcade::Vect<size_t>(lib->getMaxX(), lib->getMaxY());
	auto pos = Arcade::Vect<size_t>(0, 0);
	_pixelBox = Arcade::PixelBox(size, pos);
	auto playerPos = _player;
	playerPos.setXY((playerPos.getX() * lib->getMaxX()) / _width, (playerPos.getY() * lib->getMaxY()) / _height);
	_pixelBox.putRect(playerPos, {lib->getMaxX() / _width, lib->getMaxY() / _height}, Arcade::Color(255));
	lib->drawPixelBox(_pixelBox);
	//lib->drawText(_title);
	lib->refreshWindow();
}
