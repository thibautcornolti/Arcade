/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "SfmlGraphicLib.hpp"

Arcade::SfmlGraphicLib::SfmlGraphicLib()
	: _lastEvents()
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

void Arcade::SfmlGraphicLib::openRenderer(std::string const &title)
{
	_window.create(sf::VideoMode(_width, _height, 32), title);
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

void Arcade::SfmlGraphicLib::drawPixelBox(PixelBox const &pixelBox)
{
        sf::Texture texture;
	size_t height = pixelBox.getHeight();
	size_t width = pixelBox.getWidth();
        texture.create(width, height);
        sf::Sprite sprite(texture);
	auto *col = (unsigned char *)(&pixelBox.getPixelArray()[0]);
        texture.update(col);
        sprite.setPosition(sf::Vector2f(pixelBox.getX(), pixelBox.getY()));
        _window.draw(sprite);
}

void Arcade::SfmlGraphicLib::drawText(TextBox const &textBox)
{
	sf::Text text;
	sf::Font font;
	font.loadFromFile("lib/sfml/expressway rg.ttf");
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
	Arcade::Keys temp = Arcade::Keys::NONE;
	if (_lastEvents.size()) {
		temp = _lastEvents.back();
		_lastEvents.pop_back();
	}
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
			_lastEvents.push_back(_keymap[i].second);
			break ;
		}
	}
	return true;
}

void Arcade::SfmlGraphicLib::clearEvents()
{
	_lastEvents.clear();
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
