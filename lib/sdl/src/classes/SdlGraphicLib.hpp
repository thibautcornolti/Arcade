/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <map>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "../shared_header/IGraphicLib.hpp"

namespace Arcade {
	class SdlGraphicLib : public Arcade::IGraphicLib {
	public:
		SdlGraphicLib();
		~SdlGraphicLib() final;

		/* Get the name of the library */
		std::string getName() const final;


		/* Window handling */
		// Main loop condition
		bool isOpen() const final; 

		// Closes the window => stop loop (go menu)
		void closeRenderer() final;
		
		// Opens the window => start loop
		void openRenderer(std::string const &) final;

		// Clears the screen
		void clearWindow() final;

		// Displays the buffered frame to the screen
		void refreshWindow() final;


		/* Rendering functions */
		// Draws a PixelBox or the sprite if supported
		void drawPixelBox(PixelBox const &) final;

		// Draws a TextBox
		void drawText(TextBox const &) final;


		/* Events handling */
		// Gets the last saved event (used in render loop)
		Keys getLastEvent() final;
		
		// Saves the event in the Graphics library
		bool pollEvents() final;
		
		// Deletes the last event
		void clearEvents() final;


		/* Context Info */
		// get the X and Y max of the windows
		Vect<size_t> getScreenSize() const final;
		
		// get the Y max of the windows
		size_t getMaxY() const final;
		
		// get the X max of the windows
		size_t getMaxX() const final;
	protected:
	private:
		bool _isRendering = false;
		size_t _width = 800;
		size_t _height = 600;
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		SDL_Surface *_primarySurface;
		std::vector<Keys> _lastEvents;
		std::vector<std::pair<SDL_Keycode, Arcade::Keys>> _keymap = {
			{SDLK_a, Arcade::Keys::A},
			{SDLK_b, Arcade::Keys::B},
			{SDLK_c, Arcade::Keys::C},
			{SDLK_d, Arcade::Keys::D},
			{SDLK_e, Arcade::Keys::E},
			{SDLK_f, Arcade::Keys::F},
			{SDLK_g, Arcade::Keys::G},
			{SDLK_h, Arcade::Keys::H},
			{SDLK_i, Arcade::Keys::I},
			{SDLK_j, Arcade::Keys::J},
			{SDLK_k, Arcade::Keys::K},
			{SDLK_l, Arcade::Keys::L},
			{SDLK_m, Arcade::Keys::M},
			{SDLK_n, Arcade::Keys::N},
			{SDLK_o, Arcade::Keys::O},
			{SDLK_p, Arcade::Keys::P},
			{SDLK_q, Arcade::Keys::Q},
			{SDLK_r, Arcade::Keys::R},
			{SDLK_s, Arcade::Keys::S},
			{SDLK_t, Arcade::Keys::T},
			{SDLK_u, Arcade::Keys::U},
			{SDLK_v, Arcade::Keys::V},
			{SDLK_w, Arcade::Keys::W},
			{SDLK_x, Arcade::Keys::X},
			{SDLK_y, Arcade::Keys::Y},
			{SDLK_z, Arcade::Keys::Z},
			{SDLK_LEFT, Arcade::Keys::LEFT},
			{SDLK_RIGHT, Arcade::Keys::RIGHT},
			{SDLK_UP, Arcade::Keys::UP},
			{SDLK_DOWN, Arcade::Keys::DOWN},
			{SDLK_RETURN, Arcade::Keys::ENTER},
			{SDLK_SPACE, Arcade::Keys::SPACE},
			{SDLK_DELETE, Arcade::Keys::DELETE},
			{SDLK_BACKSPACE, Arcade::Keys::BACKSPACE},
			{SDLK_TAB, Arcade::Keys::TAB},
			{SDLK_ESCAPE, Arcade::Keys::ESC},
		};
	};
};
