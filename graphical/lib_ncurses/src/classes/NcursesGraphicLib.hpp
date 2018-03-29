/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <ncurses.h>
#include "../shared_header/IGraphicLib.hpp"

namespace Arcade {
	class NcursesGraphicLib : public Arcade::IGraphicLib {
	public:
		NcursesGraphicLib();
		~NcursesGraphicLib() final;

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
		int getMaxY() const final;
		
		// get the X max of the windows
		int getMaxX() const final;
	protected:
	private:
		bool _isRendering = false;
		Keys _lastEvent;
	};
};
