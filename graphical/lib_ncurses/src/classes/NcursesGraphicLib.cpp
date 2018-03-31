/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "NcursesGraphicLib.hpp"

Arcade::NcursesGraphicLib::NcursesGraphicLib()
	: _colors()
{}

Arcade::NcursesGraphicLib::~NcursesGraphicLib()
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

void Arcade::NcursesGraphicLib::openRenderer()
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
	Arcade::Keys temp = _lastEvent;
	clearEvents();
	return temp;
}

bool Arcade::NcursesGraphicLib::pollEvents()
{
	if (_isRendering == false)
		return false;
	auto k = getch();

	for (size_t i = 0 ; i < _keymap.size() ; ++i) {
		if (k == _keymap[i].first) {
			_lastEvent = _keymap[i].second;
			break ;
		}
	}
	return true;
}

void Arcade::NcursesGraphicLib::clearEvents()
{
	_lastEvent = Arcade::Keys::NONE;
}

Arcade::Vect<size_t> Arcade::NcursesGraphicLib::getScreenSize() const 
{
	return Arcade::Vect<size_t>(getMaxX(), getMaxY());
}

size_t Arcade::NcursesGraphicLib::getMaxY() const
{
	return LINES;
}

size_t Arcade::NcursesGraphicLib::getMaxX() const
{
	return COLS;
}

int Arcade::NcursesGraphicLib::_getPairCode(Arcade::Color f, Arcade::Color b)
{
	long fcode = f.getRed() + (f.getGreen() << 8) + (f.getBlue() << 16);
	long bcode = b.getRed() + (b.getGreen() << 8) + (b.getBlue() << 16);
	short icf = _colors[fcode];
	short icb;
	if (bcode == 0)
		icb = 0;
	else
		icb = _colors[bcode];
	double d = 1000 / 255;
	if (!icf) {
		_colors[fcode] = _nbColor;
		icf = _nbColor++;
		init_color(icf, f.getRed() * d, f.getGreen() * d,
			f.getBlue() * d);
	}
	if (!icb && b.getRed() + b.getGreen() + b.getBlue()) {
		_colors[bcode] = _nbColor;
		icb = _nbColor++;
		init_color(icb, b.getRed() * d, b.getGreen() * d,
			b.getBlue() * d);
	}
	init_pair((icf << 4) + icb, icf, icb);
	return (icf << 4) + icb;
}
