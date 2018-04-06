/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Sdl class lib
*/


#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL/SDL_ttf.h>
#include "gfx/Sdl.hpp"
#include "IGraphicLib.hpp"

Arcade::Gfx::Sdl::Sdl() : Arcade::IGraphicLib::IGraphicLib()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		exit(84);
	}
	if( TTF_Init() == -1 ) {
		std::cout << "TTF_Init Error: " << std::endl;
		exit(84);
	}
}

Arcade::Gfx::Sdl::~Sdl()
{
}

std::string Arcade::Gfx::Sdl::getName() const
{
	return "Sdl";
}

bool Arcade::Gfx::Sdl::isOpen() const
{

	return _window != nullptr;
}

void Arcade::Gfx::Sdl::closeRenderer()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Arcade::Gfx::Sdl::openRenderer(std::string const &title)
{
	_window = SDL_CreateWindow(title.c_str(), 0, 0, 1920, 1080,
		SDL_WINDOW_FULLSCREEN);
	_renderer = SDL_CreateRenderer(_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr)
		SDL_Quit();
	_font = TTF_OpenFont("./ressources/font/OpenSansRegular.ttf",
		30);


}

void Arcade::Gfx::Sdl::clearWindow()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);
}

void Arcade::Gfx::Sdl::refreshWindow()
{
	SDL_RenderPresent(_renderer);
}

Arcade::Vect<size_t> Arcade::Gfx::Sdl::getScreenSize() const
{
	return {_width, _height};
}

size_t Arcade::Gfx::Sdl::getMaxY() const
{
	return _height;
}

size_t Arcade::Gfx::Sdl::getMaxX() const
{
	return _width;
}

void Arcade::Gfx::Sdl::drawPixelBox(Arcade::PixelBox &box)
{
	size_t y = 0;
	size_t x = 0;

	for (; x < box.getWidth(); x++) {
		y = 0;
		for (; y < box.getHeight(); y++) {
			auto color = box.getPixel(Vect<size_t>(x, y));
			SDL_SetRenderDrawColor(_renderer, color.getRed(),
				color.getGreen(), color.getBlue(),
				color.getAlpha());
			SDL_RenderDrawPoint(_renderer,
				static_cast<int>(box.getX() + x),
				static_cast<int>(box.getY() + y));
		}
	}
}

void Arcade::Gfx::Sdl::drawText(Arcade::TextBox &text)
{
	if (_font == nullptr)
		std::cout << TTF_GetError() << std::endl;
	SDL_Color sdl_color = {text.getColor().getRed(),
		text.getColor().getBlue(), text.getColor().getGreen(),
		text.getColor().getAlpha()};
	SDL_Surface *surface = TTF_RenderText_Blended(_font,
		text.getValue().c_str(), sdl_color);

	SDL_Texture *message = SDL_CreateTextureFromSurface(_renderer, surface);

	SDL_Rect Message_rect;
	Message_rect.x = static_cast<int>(text.getPos().getY());
	Message_rect.y = static_cast<int>(text.getPos().getX());
	Message_rect.w = surface->w;
	Message_rect.h = surface->h;
	SDL_RenderCopy(_renderer, message, nullptr, &Message_rect);
}

Arcade::Keys Arcade::Gfx::Sdl::getLastEvent()
{
	auto elem = Arcade::Keys::DELETE;

	if (!_events.empty()) {
		elem = _events.front();
		_events.pop_front();
	}
	return elem;
}

bool Arcade::Gfx::Sdl::pollEvents()
{
	bool myBool = false;

	while (this->isOpen() && SDL_PollEvent(&_event)) {
		if (_event.type == SDL_KEYDOWN) {
			_events.push_back(keyMap.at(_event.key.keysym.sym));
			myBool = true;
		}
	}
	return myBool;
}

void Arcade::Gfx::Sdl::clearEvents()
{
}
