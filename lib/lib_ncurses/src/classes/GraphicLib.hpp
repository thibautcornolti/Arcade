/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include "../Arcade.hpp"

namespace Arcade {
	class GraphicLib : public Arcade::IGraphicLib {
		public:
			GraphicLib();
			~GraphicLib();

			virtual bool supportSprite();
			virtual bool needFont();

			virtual bool isOpen();
			virtual bool closeRendering();
			virtual bool openRendering();
			virtual void clearWindow();

			virtual bool initRenderer();
			virtual bool stopRenderer();

			virtual void drawPixelBox(Arcade::PixelBox *);
			virtual void drawText(Arcade::TextBox *);

			virtual void *loadText(std::string path);
			virtual void *loadSprite(std::string path);

			virtual void getLastEvent();
			virtual void pollEvent();
			virtual void cleanEvent();
			int oui = 1;
		protected:
		private:
	};
};
