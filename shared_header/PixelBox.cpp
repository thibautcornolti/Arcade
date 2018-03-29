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
	return _size.getY();
}

size_t Arcade::PixelBox::getHeight() const
{
	return _pos.getY();
}

void Arcade::PixelBox::setY(size_t y)
{
	_pos.setY(y);
}

void Arcade::PixelBox::setHeight(size_t height)
{
	_size.setY(height);
}

size_t Arcade::PixelBox::getX() const
{
	return _size.getX();
}

size_t Arcade::PixelBox::getWidth() const
{
	return _pos.getX();
}

void Arcade::PixelBox::setWidth(size_t width)
{
	_size.setX(width);
}

void Arcade::PixelBox::setX(size_t x)
{
	_pos.setX(x);
}

void Arcade::PixelBox::putPixel(Vect<size_t> pos, Arcade::Color col)
{
	_colorFrame[pos.getY() * _size.getX() + pos.getX()] = col;
}

Arcade::Color Arcade::PixelBox::getPixel(Vect<size_t> pos) const
{
	return _colorFrame[pos.getY() * _size.getX() + pos.getX()];
}

std::vector<Arcade::Color> &Arcade::PixelBox::getPixelArray()
{
	return _colorFrame;
}

