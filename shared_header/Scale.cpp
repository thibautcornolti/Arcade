/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scale.cpp
*/

#include <iostream>
#include <iomanip>
#include "Scale.hpp"

Arcade::Scale::Scale()
{

}

Arcade::Scale::~Scale() {}

void Arcade::Scale::setCentering(const Arcade::Scale::CENTERING &param)
{
	_param = param;
}

void Arcade::Scale::setWindowSize(const Arcade::Vect<size_t> &windowsSize)
{
	_windowSize = windowsSize;
}

void Arcade::Scale::computeCentering(Arcade::Vect<size_t> &pos, Arcade::PixelBox &pixelBox)
{
	switch (_param) {
		case HORIZONTAL:
			pos.setX(pos.getX() - pixelBox.getWidth() / 2);
			break;
		case VERTICAL:
			pos.setY(pos.getY() - pixelBox.getHeight() / 2);
			break;
		case BOTH:
			pos.setX(pos.getX() - pixelBox.getWidth() / 2);
			pos.setY(pos.getY() - pixelBox.getHeight() / 2);
			break;
		case NONE:
			break;
	}
}

void Arcade::Scale::scalePixelBox(const Arcade::Vect<size_t> &pos,
				  const Arcade::Vect<size_t> &size,
				  Arcade::PixelBox &pixelBox)
{
	Arcade::PixelBox newPixelBox = pixelBox;
	Arcade::Vect<size_t> nbPixelFree = {_windowSize.getX() * size.getX() / 100, _windowSize.getY() * size.getY() / 100};
	Arcade::Vect<size_t> posPixelBox = {_windowSize.getX() * pos.getX() / 100, _windowSize.getY() * pos.getY() / 100};
	Arcade::Vect<size_t> pixelRatio = {nbPixelFree.getX() / pixelBox.getWidth(), nbPixelFree.getY() / pixelBox.getHeight()};
	Arcade::Vect<size_t> rectPos = {0, 0};

	if (pixelRatio.getX() < 1)
		pixelRatio.setX(1);
	if (pixelRatio.getY() < 1)
		pixelRatio.setY(1);
	Arcade::PixelBox finalPixelBox({pixelRatio.getX() * newPixelBox.getWidth(), pixelRatio.getY() * newPixelBox.getHeight()}, {0, 0});
	pixelBox = finalPixelBox;
	computeCentering(posPixelBox, pixelBox);
	pixelBox.setPos({posPixelBox.getX(), posPixelBox.getY()});
	for (size_t y = 0; y < newPixelBox.getHeight(); y++) {
		for (size_t x = 0; x < newPixelBox.getWidth(); x++) {
			pixelBox.putRect({rectPos.getX(), rectPos.getY()}, {pixelRatio.getX(), pixelRatio.getY()}, newPixelBox.getPixel({x, y}));
			rectPos.setX(rectPos.getX() + pixelRatio.getX());
		}
		rectPos.setY(rectPos.getY() + pixelRatio.getY());
		rectPos.setX(0);
	}
}

void Arcade::Scale::scaleTextBox(const Arcade::Vect<double> &pos,
				 Arcade::TextBox &textBox)
{
	Arcade::Vect<double> test = {static_cast<double>(_windowSize.getX()) * pos.getX() / 100, static_cast<double>(_windowSize.getY()) * (5 * pos.getY()) / 100};

	textBox.setPos({static_cast<size_t >(test.getX()), static_cast<size_t >(test.getY())});
}