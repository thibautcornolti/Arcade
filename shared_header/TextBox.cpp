/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "TextBox.hpp"

Arcade::TextBox::TextBox(std::string const &text, size_t h, size_t w,
			size_t posH, size_t posW)
{
	setValue(text);
	setH(h);
	setW(w);
	setPosH(posH);
	setPosW(posW);
}

const std::string &Arcade::TextBox::getValue() const
{
	return _value;
}

void Arcade::TextBox::setValue(std::string const &text)
{
	_value = text;
}

size_t Arcade::TextBox::getH() const
{
	return _size.getY();
}

size_t Arcade::TextBox::getPosH() const
{
	return _pos.getY();
}

void Arcade::TextBox::setH(size_t height)
{
	_size.setY(height);
}

void Arcade::TextBox::setPosH(size_t posH)
{
	_pos.setY(posH);
}

size_t Arcade::TextBox::getW() const
{
	return _size.getX();
}

size_t Arcade::TextBox::getPosW() const
{
	return _pos.getX();
}

void Arcade::TextBox::setW(size_t width)
{
	_size.setX(width);
}

void Arcade::TextBox::setPosW(size_t posW)
{
	_pos.setX(posW);
}

Arcade::Color Arcade::TextBox::getColor() const
{
	return _color;
}

void Arcade::TextBox::setColor(Arcade::Color color)
{
	_color = color;
}
