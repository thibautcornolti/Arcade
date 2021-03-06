/*
** EPITECH PROJECT, 2018
** PixelBox
** File description:
** PixelBox
*/

#include "PixelBox.hpp"

Arcade::PixelBox::PixelBox(Vect<size_t> size, Vect<size_t> pos, Color col)
{
	_pos = pos;
	_size = size;
	for (size_t i = 0 ; i < size.getX() * size.getY() ; ++i)
		_colorFrame.push_back(col);
}

size_t Arcade::PixelBox::getY() const
{
	return _pos.getY();
}

size_t Arcade::PixelBox::getHeight() const
{
	return _size.getY();
}

void Arcade::PixelBox::setY(size_t y)
{
	_pos.setY(y);
}

void Arcade::PixelBox::setHeight(size_t height)
{
	_size.setY(height);
	_colorFrame.reserve(getWidth() * getHeight());
	for (size_t i = 0 ; i < _size.getX() * _size.getY() ; ++i)
		_colorFrame[i] = Arcade::Color();
}

size_t Arcade::PixelBox::getX() const
{
	return _pos.getX();
}

size_t Arcade::PixelBox::getWidth() const
{
	return _size.getX();
}

void Arcade::PixelBox::setWidth(size_t width)
{
	_size.setX(width);
	_colorFrame.reserve(getWidth() * getHeight());
	for (size_t i = 0 ; i < _size.getX() * _size.getY() ; ++i)
		_colorFrame[i] = Arcade::Color();
}

void Arcade::PixelBox::setX(size_t x)
{
	_pos.setX(x);
}

void Arcade::PixelBox::setPos(Arcade::Vect<size_t> pos)
{
	setX(pos.getX());
	setY(pos.getY());
}

void Arcade::PixelBox::setSize(Arcade::Vect<size_t> size)
{
	_size = size;
	_colorFrame.reserve(getWidth() * getHeight());
	for (size_t i = 0 ; i < size.getX() * size.getY() ; ++i)
		_colorFrame[i] = Arcade::Color();
}

Arcade::Vect<size_t> Arcade::PixelBox::getSize() const
{
	return {getWidth(), getHeight()};
}

Arcade::Vect<size_t> Arcade::PixelBox::getPos() const
{
	return {getX(), getY()};
}

void Arcade::PixelBox::putPixel(Vect<size_t> pos, Arcade::Color col)
{
	if (pos.getX() < _size.getX() && pos.getY() < _size.getY())
		_colorFrame[pos.getY() * _size.getX() + pos.getX()] = col;
}

void Arcade::PixelBox::putRect(Vect<size_t> pos, Vect<size_t> size, Color col)
{
        for (size_t y = 0; y < size.getY(); y++)
                for (size_t x = 0; x < size.getX(); x++)
                        putPixel(Arcade::Vect<size_t>(x + pos.getX(),
				y + pos.getY()), col);
}

Arcade::Color Arcade::PixelBox::getPixel(Vect<size_t> pos) const
{
	return _colorFrame[pos.getY() * _size.getX() + pos.getX()];
}

std::vector<Arcade::Color> const &Arcade::PixelBox::getPixelArray() const
{
	return _colorFrame;
}

