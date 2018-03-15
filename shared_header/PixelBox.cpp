/*
** EPITECH PROJECT, 2018
** PixelBox
** File description:
** PixelBox
*/

#include "PixelBox.hpp"

Arcade::PixelBox::PixelBox(size_t height, size_t width, size_t posW, size_t posH)
{
    _size = Vect<size_t>(width, height);
    _pos = Vect<size_t>(posW, posH);
}
