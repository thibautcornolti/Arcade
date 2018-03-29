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
	for (auto &graph : _graphs)
		graph->stopRenderer();
	for (auto &game : _games)
		game->stopGame();
}

void Core::close()
{
	_getGraph().closeRendering();
}

void Core::swapLib(Arcade::Keys key)
{
	if (key == Arcade::Keys::RIGHT || key == Arcade::Keys::LEFT) {
		_getGraph().closeRendering();
		_libGraphIncrementer = (_libGraphIncrementer +
			(key == Arcade::Keys::RIGHT ? 1 : -1)) % _graphs.size();
		_getGraph().openRendering();
	}
}

void Core::run()
{
	Arcade::Keys key;

	if (_graphs.size() == 0)
		return ;
	_getGraph().openRendering();
}

bool Core::_initGraphs()
{
	LibAnalyzer l;
	
	for (auto &lib : l.getGraphs()) {
		std::shared_ptr<DLLoader> dl(new DLLoader(GRAPH_FOLDER"/" + lib));
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
		_graphs.push_back(o);
	}
	return true;
}

bool Core::_initGames()
{
	LibAnalyzer l;
	
	for (auto &lib : l.getGames()) {
		std::shared_ptr<DLLoader> dl(new DLLoader(GAME_FOLDER"/" + lib));
		_loaders.push_back(dl);

		if (dl->isError()) {
			std::cout << dl->getError() << std::endl;
			return false;
		}
		auto o = dl->getInstance<Arcade::IGameLib>();
		if (dl->isError()) {
			std::cout << dl->getError() << std::endl;
			return false;
		}
		o->initGame();
		_games.push_back(o);
	}
	return true;
}

bool Core::init()
{	
	if (!_initGraphs() || !_initGames())
		return false;
	return true;
}

Arcade::IGraphicLib &Core::_getGraph()
{
	if (_graphs.size() == 0) {
		fprintf(stderr, "No lib found\n");
		exit(84);
	}
	return *(_graphs[_libGraphIncrementer % _graphs.size()]);
}

Arcade::IGameLib &Core::_getGame()
{
	if (_games.size() == 0) {
		fprintf(stderr, "No game found\n");
		exit(84);
	}
	return *(_games[_libGameIncrementer % _games.size()]);
}
