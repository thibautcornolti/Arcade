/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "SdlGraphicLib.hpp"

Arcade::SdlGraphicLib::SdlGraphicLib()
	: _lastEvents()
{
	auto ret = SDL_Init(SDL_INIT_VIDEO);
	if(ret < 0) {
    		std::cerr <<"Unable to Init SDL: "
			<< SDL_GetError()
			<< std::endl;
    		exit(84);
	}
}

Arcade::SdlGraphicLib::~SdlGraphicLib()
{
	SDL_Quit();
}

std::string Arcade::SdlGraphicLib::getName() const
{
	return "Sfml";
}

bool Arcade::SdlGraphicLib::isOpen() const
{
	return _isRendering;
}

void Arcade::SdlGraphicLib::clearWindow()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

void Arcade::SdlGraphicLib::openRenderer(std::string const &title)
{
	_window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		_width, _height, SDL_WINDOW_SHOWN
	);
	if (_window == NULL) {
		std::cerr << "Unable to create SDL Window: "
			<< SDL_GetError()
			<< std::endl;
	} else {
		_primarySurface = SDL_GetWindowSurface(_window);
		_renderer = SDL_CreateRenderer(_window, -1,
			SDL_RENDERER_ACCELERATED);
		if (_renderer == NULL)
			std::cerr << "Unable to create renderer" << std::endl;
		else
			_isRendering = true;
	}
}

void Arcade::SdlGraphicLib::closeRenderer()
{
	if(_renderer) {
		SDL_DestroyRenderer(_renderer);
		_renderer = NULL;
	}
	if(_window) {
		SDL_DestroyWindow(_window);
		_window = NULL;
	}
}

void Arcade::SdlGraphicLib::refreshWindow()
{
	SDL_RenderPresent(_renderer);
}

void Arcade::SdlGraphicLib::drawPixelBox(PixelBox const &pixelBox)
{
	auto pixels = pixelBox.getPixelArray();

	size_t x = pixelBox.getX();
	size_t y = pixelBox.getY();
	for (size_t yi = 0 ; yi < pixelBox.getHeight() ; ++yi)
		for (size_t xi = 0 ; xi < pixelBox.getWidth() ; ++xi) {
			auto c = pixelBox.getPixel(Vect<size_t>(xi, yi));
			SDL_SetRenderDrawColor(_renderer, c.getRed(),
				c.getGreen(), c.getBlue(), c.getAlpha());
			SDL_RenderDrawPoint(_renderer, xi + x, yi + y);
		}
}

void Arcade::SdlGraphicLib::drawText(TextBox const &textBox)
{
	// sf::Text text;
	// sf::Font font;
	// font.loadFromFile("graphical/lib_sfml/expressway rg.ttf");
	// text.setCharacterSize(textBox.getFontSize());
	// text.setPosition(textBox.getX(), textBox.getY());
	// auto col = textBox.getColor();
	// auto sfCol = sf::Color(col.getRed(), col.getGreen(),
	// 		col.getBlue(), col.getAlpha());
	// text.setFillColor(sfCol);
	// text.setString(textBox.getValue());
	// text.setFont(font);
	// _window.draw(text);
}

Arcade::Keys Arcade::SdlGraphicLib::getLastEvent()
{
	Arcade::Keys temp = Arcade::Keys::NONE;
	if (_lastEvents.size()) {
		temp = _lastEvents.back();
		_lastEvents.pop_back();
	}
	return temp;
}

bool Arcade::SdlGraphicLib::pollEvents()
{
	SDL_Event event;
	
	SDL_PollEvent(&event);
	if (event.type != SDL_KEYDOWN)
		return true;
	SDL_Keycode k = event.key.keysym.sym;

	for (size_t i = 0 ; i < _keymap.size() ; ++i) {
		if (k == _keymap[i].first) {
			_lastEvents.push_back(_keymap[i].second);
			break ;
		}
	}
	return true;
}

void Arcade::SdlGraphicLib::clearEvents()
{
	_lastEvents.clear();
}

Arcade::Vect<size_t> Arcade::SdlGraphicLib::getScreenSize() const 
{
	return Arcade::Vect<size_t>(getMaxX(), getMaxY());
}

size_t Arcade::SdlGraphicLib::getMaxY() const
{
	return _height;
}

size_t Arcade::SdlGraphicLib::getMaxX() const
{
	return _width;
}
