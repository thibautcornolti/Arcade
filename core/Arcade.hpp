/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

#include <string>

namespace Arcade {
	class Color {
	public:
		Color(char red=0, char green=0, char blue=0, char alpha=0);
		void setColor(char red=0, char green=0, char blue=0, char alpha=0);
		int getHexa();
		char red;
		char green;
		char blue;
		char alpha;
	};

	class PixelBox {
	public:
		size_t getH();
		size_t getPosH();
		void setH(size_t);
		void setPosH(size_t);

		size_t getW();
		size_t getPosW();
		void setW(size_t);
		void setPosW(size_t);

	private:
		void *sprite;
		Color color;
		size_t h;
		size_t w;
		size_t posh;
		size_t posw;
	};

	class TextBox {
	public:
		std::string getValue();
		void setValue(std::string);

		void *getFont();
		void setFont(void*);

		size_t getH();
		size_t getPosH();
		void setH(size_t);
		void setPosH(size_t);

		size_t getW();
		size_t getPosW();
		void setW(size_t);
		void setPosW(size_t);

	private:
		std::string value;
		void *font;
		size_t h;
		size_t w;
		size_t posh;
		size_t posw;
	};

	class IGraphicLib {
	public:
		//  Module info
		virtual bool supportSprite(); // optimize loading of res
		virtual bool needFont(); // optimize loading of res

		// Module window gestionnary
		virtual bool isOpen(); // Main loop condition
		virtual bool closeRendering(); // close the window => stop loop (go menu)
		virtual bool openRendering();  // open the window => start loop
		virtual void clearWindow(); // clear the screen

		// init Module ressources
		virtual bool initRenderer(); // Start a lib
		virtual bool stopRenderer(); // Stop a lib

		// rendering fcts
		virtual void drawPixelBox(PixelBox *); // draw a PixelBox or the sprite if supportSprite==1
		virtual void drawText(TextBox *); // draw a TextBox

		//load res
		virtual void *loadText(std::string path); //ret a text in the lib format or NULL if not native
		virtual void *loadSprite(std::string path); //ret a sprite in the lib format or NULL if not supported


		// update fcts
		virtual void getLastEvent(); // get the last event (used by loop)
		virtual void pollEvent(); // save the event in the lib module
		virtual void cleanEvent(); // delete the last event
	};

	class IGameModule {
	public:
		void loadRessource(IGraphicLib *); // called start lib
		void freeRessource(IGraphicLib *); // called on stop lib

		void update(IGraphicLib *); // Action function of the game (getch, event, …)
		void render(IGraphicLib *); // Rendering function of the game
	};

	namespace Keys {
		enum KEYS {
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			ENTER,
			SPACE,
			DELETE,
			BACK_SPACE,
			MOUSE_LEFT,
			MOUSE_RIGHT,
		};
	};

};