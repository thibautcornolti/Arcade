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
		getGame().stop();
		_inMenu = true;
	}
}

void Core::openGraph(const std::string &s)
{
	for (size_t i = 0 ; i < _graphsName.size() ; ++i)
		if (s == GRAPH_FOLDER"/" + _graphsName[i]) {
			getGraph().closeRenderer();
			_libGraphIncrementer = i;
			getGraph().openRenderer("Arcade");
		}
}

void Core::openGraph(size_t n)
{
	getGraph().closeRenderer();
	_libGraphIncrementer = n;
	getGraph().openRenderer("Arcade");
}

void Core::openGame(size_t n)
{
	_libGameIncrementer = n;
	getGame().init();
	_inMenu = false;
}

void Core::close()
{
	getGame().stop();
	getGraph().closeRenderer();
}

void Core::run(const std::string &graphLibName)
{
	Arcade::Keys key;
	Arcade::Menu menu(_gamesName, _graphsName);

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
		_graphsName.push_back(lib);
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
