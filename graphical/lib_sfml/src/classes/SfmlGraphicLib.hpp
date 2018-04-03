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
#include <SFML/Graphics.hpp>
#include "../shared_header/IGraphicLib.hpp"

namespace Arcade {
	class SfmlGraphicLib : public Arcade::IGraphicLib {
	public:
		SfmlGraphicLib();
		~SfmlGraphicLib() final;

		/* Get the name of the library */
		std::string getName() const final;


		/* Window handling */
		// Main loop condition
		bool isOpen() const final; 

		// Closes the window => stop loop (go menu)
		void closeRenderer() final;
		
		// Opens the window => start loop
		void openRenderer() final;
		
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
		size_t _width = 800;
		size_t _height = 600;
		sf::RenderWindow _window;
		Keys _lastEvent = Arcade::Keys::NONE;
		std::vector<std::pair<sf::Keyboard::Key, Arcade::Keys>> _keymap = {
			{sf::Keyboard::A, Arcade::Keys::A},
			{sf::Keyboard::B, Arcade::Keys::B},
			{sf::Keyboard::C, Arcade::Keys::C},
			{sf::Keyboard::D, Arcade::Keys::D},
			{sf::Keyboard::E, Arcade::Keys::E},
			{sf::Keyboard::F, Arcade::Keys::F},
			{sf::Keyboard::G, Arcade::Keys::G},
			{sf::Keyboard::H, Arcade::Keys::H},
			{sf::Keyboard::I, Arcade::Keys::I},
			{sf::Keyboard::J, Arcade::Keys::J},
			{sf::Keyboard::K, Arcade::Keys::K},
			{sf::Keyboard::L, Arcade::Keys::L},
			{sf::Keyboard::M, Arcade::Keys::M},
			{sf::Keyboard::N, Arcade::Keys::N},
			{sf::Keyboard::O, Arcade::Keys::O},
			{sf::Keyboard::P, Arcade::Keys::P},
			{sf::Keyboard::Q, Arcade::Keys::Q},
			{sf::Keyboard::R, Arcade::Keys::R},
			{sf::Keyboard::S, Arcade::Keys::S},
			{sf::Keyboard::T, Arcade::Keys::T},
			{sf::Keyboard::U, Arcade::Keys::U},
			{sf::Keyboard::V, Arcade::Keys::V},
			{sf::Keyboard::W, Arcade::Keys::W},
			{sf::Keyboard::X, Arcade::Keys::X},
			{sf::Keyboard::Y, Arcade::Keys::Y},
			{sf::Keyboard::Z, Arcade::Keys::Z},
			{sf::Keyboard::Left, Arcade::Keys::LEFT},
			{sf::Keyboard::Right, Arcade::Keys::RIGHT},
			{sf::Keyboard::Up, Arcade::Keys::UP},
			{sf::Keyboard::Down, Arcade::Keys::DOWN},
			{sf::Keyboard::Return, Arcade::Keys::ENTER},
			{sf::Keyboard::Space, Arcade::Keys::SPACE},
			{sf::Keyboard::Delete, Arcade::Keys::DELETE},
			{sf::Keyboard::BackSpace, Arcade::Keys::BACKSPACE},
			{sf::Keyboard::Tab, Arcade::Keys::TAB},
			{sf::Keyboard::Escape, Arcade::Keys::ESC},
		};
	};
};
