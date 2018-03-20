/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "Core.hpp"

Core::Core()
{
}

Core::~Core()
{
}

void Core::stop()
{
	close();
	for (auto &lib : _libs)
		lib->stopRenderer();
}

void Core::close()
{
	_getLib().closeRendering();
}

void Core::swapLib(Arcade::Keys key)
{
	if (key == Arcade::Keys::RIGHT || key == Arcade::Keys::LEFT) {
		_getLib().closeRendering();
		_libIncrementer = (_libIncrementer +
			(key == Arcade::Keys::RIGHT ? 1 : -1)) % _libs.size();
		_getLib().openRendering();
	}
}

void Core::run()
{
	Arcade::Keys key;

	if (_libs.size() == 0)
		return ;
	_getLib().openRendering();
	while (_getLib().isOpen()) {
		_getLib().pollEvent();
		key = _getLib().getLastEvent();
		_getLib().cleanEvent();
		if (key != Arcade::Keys::NONE) {
			swapLib(key);
			if (key == Arcade::Keys::ESC) {
				close();
				break ;
			}
		}
		auto a = Arcade::PixelBox(10, 10, 10, 10);
		a.putPixel(Arcade::Vect<size_t>(4, 0), Arcade::Color(0, 0, 0, 1));
		auto b = Arcade::TextBox("salut", 0, 0, 15, 10);
		_getLib().drawPixelBox(&a);
		_getLib().drawText(&b);
		_getLib().refreshWindow();
	}
}

bool Core::init()
{	
	LibAnalyzer l;

	for (auto &lib : l.getLibs()) {
		std::shared_ptr<DLLoader> dl(new DLLoader(LIB_FOLDER"/" + lib));
		_loaders.push_back(dl);

		if (dl->isError()) {
			std::cout << dl->getError() << std::endl;
			return false;
		}
		auto o = dl->getInstance<Arcade::IGraphicLib>();
		if (dl->isError()) {
			std::cout << dl->getError() << std::endl;
			return false;
		}
		o->initRenderer();
		_libs.push_back(o);
	}
	return true;
}

Arcade::IGraphicLib &Core::_getLib()
{
	return *(_libs[_libIncrementer % _libs.size()]);
}
