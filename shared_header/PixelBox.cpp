/*
** EPITECH PROJECT, 2018
** PixelBox
** File description:
** PixelBox
*/

#include "PixelBox.hpp"

Arcade::PixelBox::PixelBox(size_t height, size_t width, size_t posW, size_t posH)
{
    _size = Vect<size_t>(width, height);
    _pos = Vect<size_t>(posW, posH);
}

size_t Arcade::PixelBox::getH() const
{
	return _size.getY();
}

size_t Arcade::PixelBox::getPosH() const
{
	return _pos.getY();
}

void Arcade::PixelBox::setH(size_t height)
{
	_size.setY(height);
}

void Arcade::PixelBox::setPosH(size_t posH)
{
	_pos.setY(posH);
}

size_t Arcade::PixelBox::getW() const
{
	return _size.getX();
}

size_t Arcade::PixelBox::getPosW() const
{
	return _pos.getX();
}

void Arcade::PixelBox::setW(size_t width)
{
	_size.setX(width);
}

void Arcade::PixelBox::setPosW(size_t posW)
{
	_pos.setX(posW);
}

void Arcade::PixelBox::setColor(Color &color)
{
	_color = color;
}

Arcade::Color &Arcade::PixelBox::getColor()
{
	return _color;
}

void Arcade::PixelBox::setSprite(void *sprite)
{
	_sprite = sprite;
}

void *Arcade::PixelBox::getSprite()
{
	return _sprite;
}
