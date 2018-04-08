/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "SdlGraphicLib.hpp"

Arcade::SdlGraphicLib::SdlGraphicLib()
	: _lastEvents()
	, _title()
{
	auto ret = SDL_Init(SDL_INIT_VIDEO);
	if(ret < 0) {
    		std::cerr <<"Unable to Init SDL: "
			<< SDL_GetError()
			<< std::endl;
    		exit(84);
	}
	ret = TTF_Init();
	if(ret < 0) {
    		std::cerr <<"Unable to Init TTF: "
			<< TTF_GetError()
			<< std::endl;
    		exit(84);
	}
}

Arcade::SdlGraphicLib::~SdlGraphicLib()
{
	TTF_Quit();
	SDL_Quit();
}

std::string Arcade::SdlGraphicLib::getName() const
{
	return "Sdl";
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
	_title = title;
	_window = SDL_CreateWindow(
		_title.c_str(),
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
	if (textBox.getValue().size() == 0)
		return ;
	TTF_Font *font = TTF_OpenFont("assets/font/expressway rg.ttf",
		textBox.getFontSize());
	if (font == NULL)
		return ;
	Arcade::Color c = textBox.getColor();
	SDL_Color col = {c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()};
	auto t = TTF_RenderText_Blended(font, textBox.getValue().c_str(), col);
	if (t == NULL)
		return ;
	SDL_Texture *text = SDL_CreateTextureFromSurface(_renderer, t);
	SDL_Rect text_rect;
	text_rect.x = static_cast<int>(textBox.getPos().getX());
	text_rect.y = static_cast<int>(textBox.getPos().getY());
	text_rect.w = t->w;
	text_rect.h = t->h;
	SDL_RenderCopy(_renderer, text, nullptr, &text_rect);
	TTF_CloseFont(font);
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
