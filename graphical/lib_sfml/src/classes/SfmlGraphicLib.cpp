/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "SfmlGraphicLib.hpp"

Arcade::SfmlGraphicLib::SfmlGraphicLib()
{}

Arcade::SfmlGraphicLib::~SfmlGraphicLib()
{}

std::string Arcade::SfmlGraphicLib::getName() const
{
	return "Sfml";
}

bool Arcade::SfmlGraphicLib::isOpen() const
{
	return _window.isOpen();
}

void Arcade::SfmlGraphicLib::clearWindow()
{
	_window.clear();
}

void Arcade::SfmlGraphicLib::openRenderer()
{
	_window.create(sf::VideoMode(_width, _height, 32), "Arcade");
	_window.setVerticalSyncEnabled(true);
}

void Arcade::SfmlGraphicLib::closeRenderer()
{
	_window.close();
}

void Arcade::SfmlGraphicLib::refreshWindow()
{
	_window.display();
}

void Arcade::SfmlGraphicLib::drawPixelBox(PixelBox &pixelBox)
{
	size_t x = pixelBox.getX();
	size_t y = pixelBox.getY();
	for (size_t yi = 0 ; yi < pixelBox.getHeight() ; ++yi)
		for (size_t xi = 0 ; xi < pixelBox.getWidth() ; ++xi) {
			Arcade::Color c = pixelBox.getPixel(Vect<size_t>(xi, yi));
			
		}
}

void Arcade::SfmlGraphicLib::drawText(TextBox &textBox)
{
	sf::Text text;
	sf::Font font;
	font.loadFromFile("graphical/lib_sfml/expressway rg.ttf");
	text.setCharacterSize(textBox.getFontSize());
	text.setPosition(textBox.getX(), textBox.getY());
	auto col = textBox.getColor();
	auto sfCol = sf::Color(col.getRed(), col.getGreen(),
			col.getBlue(), col.getAlpha());
	text.setFillColor(sfCol);
	text.setString(textBox.getValue());
	text.setFont(font);
	_window.draw(text);
}

Arcade::Keys Arcade::SfmlGraphicLib::getLastEvent()
{
	Arcade::Keys temp = _lastEvent;
	clearEvents();
	return temp;
}

bool Arcade::SfmlGraphicLib::pollEvents()
{
	sf::Event event;
	_window.pollEvent(event);
	if (event.type != sf::Event::KeyPressed)
		return true;
	sf::Keyboard::Key k = event.key.code;

	for (size_t i = 0 ; i < _keymap.size() ; ++i) {
		if (k == _keymap[i].first) {
			_lastEvent = _keymap[i].second;
			break ;
		}
	}
	return true;
}

void Arcade::SfmlGraphicLib::clearEvents()
{
	_lastEvent = Arcade::Keys::NONE;
}

Arcade::Vect<size_t> Arcade::SfmlGraphicLib::getScreenSize() const 
{
	return Arcade::Vect<size_t>(getMaxX(), getMaxY());
}

size_t Arcade::SfmlGraphicLib::getMaxY() const
{
	return _height;
}

size_t Arcade::SfmlGraphicLib::getMaxX() const
{
	return _width;
}
