/*
** EPITECH PROJECT, 2018
** Project
** File description:
** Manu.cpp
*/

#include "Menu.hpp"

Arcade::Menu::Menu(
		std::vector<std::string> &games,
		std::vector<std::string> &graphs
	)
	: _games(games)
	, _graphs(graphs)
	, _keyboard({{Arcade::Keys::DELETE, std::bind(&Arcade::Menu::resetPlayer, this)},
		     {Arcade::Keys::SPACE, std::bind(&Arcade::Menu::activeCaps, this)},
		     {Arcade::Keys::BACKSPACE, std::bind(&Arcade::Menu::removeLetter, this)},
		     {Arcade::Keys::A, std::bind(&Arcade::Menu::addLetter, this, 'a')},
		     {Arcade::Keys::B, std::bind(&Arcade::Menu::addLetter, this, 'b')},
		     {Arcade::Keys::C, std::bind(&Arcade::Menu::addLetter, this, 'c')},
		     {Arcade::Keys::D, std::bind(&Arcade::Menu::addLetter, this, 'd')},
		     {Arcade::Keys::E, std::bind(&Arcade::Menu::addLetter, this, 'e')},
		     {Arcade::Keys::F, std::bind(&Arcade::Menu::addLetter, this, 'f')},
		     {Arcade::Keys::G, std::bind(&Arcade::Menu::addLetter, this, 'g')},
		     {Arcade::Keys::H, std::bind(&Arcade::Menu::addLetter, this, 'h')},
		     {Arcade::Keys::I, std::bind(&Arcade::Menu::addLetter, this, 'i')},
		     {Arcade::Keys::J, std::bind(&Arcade::Menu::addLetter, this, 'j')},
		     {Arcade::Keys::K, std::bind(&Arcade::Menu::addLetter, this, 'k')},
		     {Arcade::Keys::L, std::bind(&Arcade::Menu::addLetter, this, 'l')},
		     {Arcade::Keys::M, std::bind(&Arcade::Menu::addLetter, this, 'm')},
		     {Arcade::Keys::N, std::bind(&Arcade::Menu::addLetter, this, 'n')},
		     {Arcade::Keys::O, std::bind(&Arcade::Menu::addLetter, this, 'o')},
		     {Arcade::Keys::P, std::bind(&Arcade::Menu::addLetter, this, 'p')},
		     {Arcade::Keys::Q, std::bind(&Arcade::Menu::addLetter, this, 'q')},
		     {Arcade::Keys::R, std::bind(&Arcade::Menu::addLetter, this, 'r')},
		     {Arcade::Keys::S, std::bind(&Arcade::Menu::addLetter, this, 's')},
		     {Arcade::Keys::T, std::bind(&Arcade::Menu::addLetter, this, 't')},
		     {Arcade::Keys::U, std::bind(&Arcade::Menu::addLetter, this, 'u')},
		     {Arcade::Keys::V, std::bind(&Arcade::Menu::addLetter, this, 'v')},
		     {Arcade::Keys::W, std::bind(&Arcade::Menu::addLetter, this, 'w')},
		     {Arcade::Keys::X, std::bind(&Arcade::Menu::addLetter, this, 'x')},
		     {Arcade::Keys::Y, std::bind(&Arcade::Menu::addLetter, this, 'y')},
		     {Arcade::Keys::Z, std::bind(&Arcade::Menu::addLetter, this, 'z')}})
{
	_score = new Scoreboard("General", "Master");
	_scale = new Scale();
}

void Arcade::Menu::activeCaps()
{
	_capsActive = (!_capsActive) ? true : false;
}

void Arcade::Menu::resetPlayer()
{
	_playerName.clear();
}

void Arcade::Menu::removeLetter()
{
	if (!_playerName.empty())
		_playerName.erase(_playerName.end()-1);
}

void Arcade::Menu::addLetter(char letter)
{
	if (_capsActive)
		letter -= 32;
	if (_playerName.size() <= 20)
		_playerName += letter;
}

void Arcade::Menu::displayScoreboard(Arcade::IGraphicLib &lib)
{
	Arcade::PixelBox background({1, 1}, {0, 0});

	_scale->setCentering(Scale::CENTERING::VERTICAL);
	_scale->scalePixelBox({50, 50}, {45, 80}, background);
	lib.drawPixelBox(background);
}

void Arcade::Menu::selector(Arcade::IGraphicLib &lib)
{
	Arcade::TextBox games("", {0, 0}, 25);
	double line = 5;

	for (size_t i = 0; i < _games.size(); i++) {
		if (i == _selection) {
			games.setValue("==> " + _games[i] + " <==");
			_scale->scaleTextBox({15, line}, games);
		} else {
			games.setValue(_games[i]);
			_scale->scaleTextBox({20, line}, games);
		}
		lib.drawText(games);
		line += 5;
	}
}

void Arcade::Menu::applyEvent(Arcade::Keys key, Arcade::Core &core)
{
	if (_keyboard.count(key))
		_keyboard[key]();
	switch (key) {
		case Arcade::Keys::DOWN:
			if (_selection < _games.size() - 1)
				_selection++;
			else
				_selection = 0;
			break;
		case Arcade::Keys::UP:
			if (_selection > 0)
				_selection--;
			else
				_selection = _games.size() - 1;
			break;
		case Arcade::Keys::ENTER:
			core.openGame(_selection);
		default:
			break;
	}
}

void Arcade::Menu::refresh(Arcade::IGraphicLib &graph)
{
	Arcade::TextBox playerName("", {0, 0}, 20);
	Arcade::TextBox caps("CAPS ACTIVE", {0, 0}, 10);
	Arcade::TextBox player("Player: ", {0, 0}, 20);

	graph.clearWindow();
	playerName.setValue(_playerName);
	_scale->setWindowSize({graph.getMaxX(), graph.getMaxY()});
	_scale->scaleTextBox({0, 0}, player);
	_scale->scaleTextBox({10, 0}, playerName);
	selector(graph);
	displayScoreboard(graph);
	if (_capsActive) {
		_scale->scaleTextBox({10, 0.7}, caps);
		graph.drawText(caps);
	}
	graph.drawText(player);
	graph.drawText(playerName);
	graph.refreshWindow();
}
