/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "Core.hpp"
#include "Menu.hpp"

void Core::swapLib(Arcade::Keys key)
{
	if (key == Arcade::Keys::RIGHT || key == Arcade::Keys::LEFT) {
		getGraph().closeRenderer();
		_libGraphIncrementer = (_libGraphIncrementer +
			(key == Arcade::Keys::RIGHT ? 1 : -1)) % _graphs.size();
		getGraph().openRenderer("Arcade");
	} else if (key == Arcade::Keys::ESC && !_inMenu) {
		getGame().close();
		_inMenu = true;
	}
}

void Core::openGraph(const std::string &s)
{
	for (size_t i = 0 ; i <_graphPaths.size() ; ++i)
		if (s == _graphPaths[i]) {
			getGraph().closeRenderer();
			_libGraphIncrementer = i;
			getGraph().openRenderer("Arcade");
		}
}

void Core::openGame(size_t n)
{
	_libGameIncrementer = n;
	getGame().open();
	_inMenu = false;
}

void Core::close()
{
	if (!_inMenu)
		getGame().close();
	for (auto &g : _games)
		g->stop();
	getGraph().closeRenderer();
}

void Core::run(const std::string &graphLibName)
{
	Arcade::Keys key;
	Menu menu(_gamesName);

	if (_graphs.size() == 0)
		return ;
	getGraph().openRenderer("Arcade");
	openGraph(graphLibName);
	while (getGraph().isOpen()) {
		getGraph().clearEvents();
		getGraph().pollEvents();
		key = getGraph().getLastEvent();
		if (key == Arcade::Keys::ESC && _inMenu)
			return close();
		else
			swapLib(key);
		if (_inMenu) {
			menu.applyEvent(key, *this);
			menu.refresh(getGraph());
		} else {
			getGame().applyEvent(key);
			getGame().update();
			getGame().refresh(getGraph());
		}
	}
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
		_graphPaths.push_back(GRAPH_FOLDER"/" + lib);
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
		o->init();
		_games.push_back(o);
		_gamesName.push_back(o->getName());
	}
	return true;
}

bool Core::init()
{	
	if (!_initGraphs() || !_initGames())
		return false;
	return true;
}

Arcade::IGraphicLib &Core::getGraph()
{
	return *(_graphs[_libGraphIncrementer % _graphs.size()]);
}

Arcade::IGameLib &Core::getGame()
{
	if (_games.size() == 0) {
		fprintf(stderr, "No game found\n");
		exit(84);
	}
	return *(_games[_libGameIncrementer % _games.size()]);
}
