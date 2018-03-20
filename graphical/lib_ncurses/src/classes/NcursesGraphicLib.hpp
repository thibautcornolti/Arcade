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
		std::string getName() final;

		/* Module info: Used to optimize initialization */
		bool supportSprite() const final;
		bool supportSound() const final;
		bool needFont() const final;


		/* Window handling */
		// Main loop condition
		bool isOpen() const final;

		// Closes the window => stop loop (go menu)
		bool closeRendering() final;
		
		// Opens the window => start loop
		bool openRendering() final;
		
		// Clears the screen
		void clearWindow() final;

		// Displays the buffered frame to the screen
		void refreshWindow() final;


		/* Resources handling */
		// Initializes the library
		bool initRenderer() final;
		
		// Unloads the library
		bool stopRenderer() final;


		/* Rendering functions */
		// Draws a PixelBox or the sprite if supported
		void drawPixelBox(PixelBox *) final;
		
		// Draws a TextBox
		void drawText(TextBox *) final;


		/* Sound functions */
		// Plays sound passed in arg
		void playSound(void *) final;
		
		// Pauses sound passed in arg
		void pauseSound(void *) final;
		
		// Stops sound passed in arg
		void stopSound(void *) final;


		/* Loading functions */
		// Returns a text font in the Graphics library format
		// or NULL if not supported
		void *loadTextFont(std::string path) final;
		
		// Returns a sprite in the Graphics library format
		// or NULL if not supported
		void *loadSprite(std::string path) final;
		
		// Returns a sound in the Graphics library format
		// or NULL if not supported
		void *loadSound(std::string path) final;


		/* Events handling */
		// Gets the last saved event (used in render loop)
		Keys getLastEvent() final;
		
		// Saves the event in the Graphics library
		bool pollEvent() final;
		
		// Deletes the last event
		void cleanEvent() final;


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
