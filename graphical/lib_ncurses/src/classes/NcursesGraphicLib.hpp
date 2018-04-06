/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <map>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>
#include "../shared_header/IGraphicLib.hpp"

namespace Arcade {
	class NcursesGraphicLib : public Arcade::IGraphicLib {
	public:
		NcursesGraphicLib();
		~NcursesGraphicLib() final = default;

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
		void drawPixelBox(PixelBox &) final;
		
		// Draws a TextBox
		void drawText(TextBox &) final;


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
		int _getPairCode(Arcade::Color, Arcade::Color);
		int _getColorCode(Arcade::Color);
		std::map<long, short> _colorToCode;
		std::map<long, short> _codeToPair;
		time_t _lastRefresh = 0;
		short _nbColor = 1;
		bool _isRendering = false;
		std::vector<Keys> _lastEvents;
		std::vector<std::pair<int, Arcade::Keys>> _keymap = {
			{'a', Arcade::Keys::A},
			{'b', Arcade::Keys::B},
			{'c', Arcade::Keys::C},
			{'d', Arcade::Keys::D},
			{'e', Arcade::Keys::E},
			{'f', Arcade::Keys::F},
			{'g', Arcade::Keys::G},
			{'h', Arcade::Keys::H},
			{'i', Arcade::Keys::I},
			{'j', Arcade::Keys::J},
			{'k', Arcade::Keys::K},
			{'l', Arcade::Keys::L},
			{'m', Arcade::Keys::M},
			{'n', Arcade::Keys::N},
			{'o', Arcade::Keys::O},
			{'p', Arcade::Keys::P},
			{'q', Arcade::Keys::Q},
			{'r', Arcade::Keys::R},
			{'s', Arcade::Keys::S},
			{'t', Arcade::Keys::T},
			{'u', Arcade::Keys::U},
			{'v', Arcade::Keys::V},
			{'w', Arcade::Keys::W},
			{'x', Arcade::Keys::X},
			{'y', Arcade::Keys::Y},
			{'z', Arcade::Keys::Z},
			{KEY_LEFT, Arcade::Keys::LEFT},
			{KEY_RIGHT, Arcade::Keys::RIGHT},
			{KEY_UP, Arcade::Keys::UP},
			{KEY_DOWN, Arcade::Keys::DOWN},
			{10, Arcade::Keys::ENTER},
			{32, Arcade::Keys::SPACE},
			{KEY_DC, Arcade::Keys::DELETE},
			{127, Arcade::Keys::BACKSPACE},
			{KEY_STAB, Arcade::Keys::TAB},
			{27, Arcade::Keys::ESC},
			{KEY_MOUSE, Arcade::Keys::MOUSELEFT},
			{KEY_MOUSE, Arcade::Keys::MOUSERIGHT}
		};
	};
};
