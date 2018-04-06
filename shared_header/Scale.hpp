/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scale.hpp
*/

#ifndef CPP_ARCADE_SCALE_HPP
#define CPP_ARCADE_SCALE_HPP

#include <string>
#include "Vect.hpp"
#include "PixelBox.hpp"
#include "TextBox.hpp"

namespace Arcade {

	class Scale {
		public:
			Scale();
			~Scale();

			enum CENTERING {
				NONE,
				HORIZONTAL,
				VERTICAL,
				BOTH
			};

			void setCentering(const CENTERING&);
			void setWindowSize(const Arcade::Vect<size_t> &windowsSize);

			void scalePixelBox(const Arcade::Vect<size_t> &pos, const Arcade::Vect<size_t> &size, Arcade::PixelBox &pixelBox);
			void scaleTextBox(const Arcade::Vect<double> &pos, Arcade::TextBox &textBox);

		private:
			void computeCentering(Arcade::Vect<size_t> &pos, Arcade::PixelBox &pixelBox);

		private:
			Arcade::Vect<size_t> _windowSize;
			CENTERING _param = NONE;
	};

}

#endif //CPP_ARCADE_SCALE_HPP
