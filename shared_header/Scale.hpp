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

/*!
 * @namespace Arcade
 * @brief Arcade project namespace
 */
namespace Arcade {

	/*!
	 * @class Scale
	 * @brief Scale class
	 *
	 * Class used to scale PixelBoxes
	 *
	 */
	class Scale {
	public:
		/*!
		 * @brief Scale class's constructor
		 * Creates a new Scale class instance.
		 *
		 */
		Scale();

		/*!
		 * @brief Scale class's destructor
		 */
		~Scale();

		/*!
		 * @brief Enumeration used by setCentering method
		 */
		enum CENTERING {
			NONE,
			HORIZONTAL,
			VERTICAL,
			BOTH
		};

		/*!
		 * @brief Scale centering's setter
		 * 
		 * Allows the user to define the desired alignment
		 * (only working on PixelBox object).
		 * By default, alignment is set to NONE which means that
		 * the PixelBox object will be set starting from
		 * the exact position set by the scalePixelBox method.
		 * 
		 */
		void setCentering(const CENTERING&);

		/*!
		 * @brief Scale window size's setter
		 * 
		 * Allows the user to set the window size.
		 * If not set, the scaling class may just explode and create
		 * a black hole destroying our world.
		 * You probably don’t want that.
		 * 
		 */
		void setWindowSize(const Arcade::Vect<size_t> &windowsSize);

		/*!
		 * @brief Scale main function for PixelBoxes
		 * 
		 * Modifies the PixelBox giving as parameter and sets
		 * the position and size using the Arcade::Vect pos and size.
		 * Your PixelBox object giving as parameter must be
		 * set with the minimal size possible to
		 * prevent a possible partial display.
		 */
		void scalePixelBox(const Arcade::Vect<size_t> &pos, const Arcade::Vect<size_t> &size, Arcade::PixelBox &pixelBox);

		/*!
		 * @brief Scale main function for TextBoxes
		 * 
		 * Modifies the TextBox giving as parameter and sets
		 * the position using the Arcade::Vect pos.
		 * Position can be set as double to allow a better vertical
		 * precision alignment for advanced graphical libs.
		 * @image html scale_textbox.png
		 * @image latex scale_textbox.png
		 * 
		 */
		void scaleTextBox(const Arcade::Vect<double> &pos, Arcade::TextBox &textBox);

	private:
		void computeCentering(Arcade::Vect<size_t> &pos, Arcade::PixelBox &pixelBox);

	private:
		Arcade::Vect<size_t> _windowSize;
		CENTERING _param = NONE;
	};

}

#endif //CPP_ARCADE_SCALE_HPP
