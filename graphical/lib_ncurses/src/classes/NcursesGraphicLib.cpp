/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "NcursesGraphicLib.hpp"

Arcade::NcursesGraphicLib::NcursesGraphicLib()
	: _colorToCode()
	, _codeToPair()
	, _lastEvents()
{}

std::string Arcade::NcursesGraphicLib::getName() const
{
	return "NCurses";
}

bool Arcade::NcursesGraphicLib::isOpen() const
{
	return _isRendering;
}

void Arcade::NcursesGraphicLib::clearWindow()
{
	clear();
}

void Arcade::NcursesGraphicLib::openRenderer(std::string const &)
{
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	start_color();
	timeout(0);
	_isRendering = true;
}

void Arcade::NcursesGraphicLib::closeRenderer()
{
	endwin();
	_isRendering = false;
}

void Arcade::NcursesGraphicLib::refreshWindow()
{
	auto current = time(NULL);
	auto spent = current - _lastRefresh;
	usleep(16000 - spent % 16000);
	_lastRefresh = current;
	refresh();
}

void Arcade::NcursesGraphicLib::drawPixelBox(PixelBox &pixelBox)
{
	size_t x = pixelBox.getX();
	size_t y = pixelBox.getY();
	for (size_t yi = 0 ; yi < pixelBox.getHeight() ; ++yi)
		for (size_t xi = 0 ; xi < pixelBox.getWidth() ; ++xi) {
			int ic = _getPairCode(
				pixelBox.getPixel(Vect<size_t>(xi, yi)),
				pixelBox.getPixel(Vect<size_t>(xi, yi)));
			attron(COLOR_PAIR(ic));
			mvprintw(yi + y, xi + x, " ");
			attroff(COLOR_PAIR(ic));
		}
}

void Arcade::NcursesGraphicLib::drawText(TextBox &textBox)
{
	int ic = _getPairCode(textBox.getColor(), textBox.getBackgroundColor());
	attron(COLOR_PAIR(ic));
	mvprintw(textBox.getY(), textBox.getX(),
		textBox.getValue().c_str());
	attroff(COLOR_PAIR(ic));
}

Arcade::Keys Arcade::NcursesGraphicLib::getLastEvent()
{
	Arcade::Keys temp = Arcade::Keys::NONE;
	if (_lastEvents.size()) {
		temp = _lastEvents.back();
		_lastEvents.pop_back();
	}
	return temp;
}

bool Arcade::NcursesGraphicLib::pollEvents()
{
	if (_isRendering == false)
		return false;
	auto k = getch();

	for (size_t i = 0 ; i < _keymap.size() ; ++i) {
		if (k == _keymap[i].first) {
			_lastEvents.push_back(_keymap[i].second);
			break ;
		}
	}
	return true;
}

void Arcade::NcursesGraphicLib::clearEvents()
{
	_lastEvents.clear();
}

Arcade::Vect<size_t> Arcade::NcursesGraphicLib::getScreenSize() const 
{
	return {getMaxX(), getMaxY()};
}

size_t Arcade::NcursesGraphicLib::getMaxY() const
{
	return LINES + 1;
}

size_t Arcade::NcursesGraphicLib::getMaxX() const
{
	return COLS + 1;
}

int Arcade::NcursesGraphicLib::_getColorCode(Arcade::Color c)
{
	long code = c.getRed() + (c.getGreen() << 8) + (c.getBlue() << 16);
	if (!code)
		return COLOR_BLACK;
	if (!_colorToCode[code])
		_colorToCode[code] = _nbColor++ % (COLOR_PAIRS - 1);
	double d = 1000 / 255;
	init_color(_colorToCode[code], c.getRed() * d, c.getGreen() * d, c.getBlue() * d);
	return _colorToCode[code];
}

int Arcade::NcursesGraphicLib::_getPairCode(Arcade::Color f, Arcade::Color b)
{
	short code_front;
	short code_back;
	short code_pair;
	long shift_pair;

	code_front = _getColorCode(f);
	code_back = _getColorCode(b);
	shift_pair =  code_front + (code_back << 16);
	if (!_codeToPair[shift_pair]) {
		code_pair = _nbColor % (COLOR_PAIRS - 1);
		_codeToPair[shift_pair] = _nbColor++ % (COLOR_PAIRS - 1);
	} else
		code_pair = _codeToPair[shift_pair];
	init_pair(code_pair, code_front, code_back);
	return code_pair;
}
