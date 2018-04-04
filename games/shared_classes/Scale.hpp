/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scale.hpp
*/

#ifndef CPP_ARCADE_SCALE_HPP
#define CPP_ARCADE_SCALE_HPP

#include <string>
#include "../../shared_header/Vect.hpp"
#include "../snake/src/shared_header/PixelBox.hpp"

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
			void scalePixelBox(const Arcade::Vect<size_t> &pos, const Arcade::Vect<size_t> &size, Arcade::PixelBox &pixelBox);
			void setWindowSize(const Arcade::Vect<size_t> &windowsSize);

		private:
			void computeCentering(Arcade::Vect<size_t> &pos, Arcade::PixelBox &pixelBox);

		private:
			Arcade::Vect<size_t> _windowSize;
			CENTERING _param = NONE;
	};

}

#endif //CPP_ARCADE_SCALE_HPP
