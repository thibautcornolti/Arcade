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

			bool supportSprite() final;
			bool needFont() final;

			bool isOpen() final;
			bool closeRendering() final;
			bool openRendering() final;
			void clearWindow() final;

			bool initRenderer() final;
			bool stopRenderer() final;

			void drawPixelBox(Arcade::PixelBox *) final;
			void drawText(Arcade::TextBox *) final;

			void *loadText(std::string path) final;
			void *loadSprite(std::string path) final;

			void getLastEvent() final;
			void pollEvent() final;
			void cleanEvent() final;
			int oui = 1;
		protected:
		private:
	};
};
