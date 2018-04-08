/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include "Core.hpp"
#include "Menu.hpp"

void Arcade::Core::swapLib(Arcade::Keys key)
{
	if (key == Arcade::Keys::RIGHT || key == Arcade::Keys::LEFT) {
		getGraph().closeRenderer();
		_libGraphIncrementer = (_graphs.size() + _libGraphIncrementer +
			(key == Arcade::Keys::RIGHT ? 1 : -1)) % _graphs.size();
		getGraph().openRenderer("Arcade");
	} else if (!_inMenu && 
		(key == Arcade::Keys::UP || key == Arcade::Keys::DOWN)) {
		getGame().stop();
		_libGameIncrementer = (_games.size() + _libGameIncrementer +
			(key == Arcade::Keys::DOWN ? 1 : -1)) % _games.size();
		getGame().init();
	} else if (key == Arcade::Keys::ESC && !_inMenu) {
		getGame().stop();
		_inMenu = true;
	}
}

void Arcade::Core::openGraph(const std::string &s)
{
	for (size_t i = 0 ; i < _graphsName.size() ; ++i)
		if (s == GRAPH_FOLDER"/" + _graphsName[i]) {
			getGraph().closeRenderer();
			_libGraphIncrementer = i;
			getGraph().openRenderer("Arcade");
		}
}

void Arcade::Core::openGraph(size_t n)
{
	getGraph().closeRenderer();
	_libGraphIncrementer = n;
	getGraph().openRenderer("Arcade");
}

void Arcade::Core::openGame(size_t n)
{
	_libGameIncrementer = n;
	getGame().init();
	_inMenu = false;
}

void Arcade::Core::close()
{
	getGame().stop();
	getGraph().closeRenderer();
}

bool Arcade::Core::_update(Arcade::Menu *menu, Arcade::Keys key)
{
	bool mustContinue = true;
	if (_inMenu) {
		menu->applyEvent(key, *this);
		menu->refresh(getGraph());
	} else {
		getGame().applyEvent(key);
		mustContinue = getGame().update();
		getGame().refresh(getGraph());
	}
	return mustContinue;
}

void Arcade::Core::run()
{
	Arcade::Keys key;
	Arcade::Menu menu(_gamesName, _graphsName);

	if (_graphs.size() == 0)
		return ;
	getGraph().openRenderer("Arcade");
	while (getGraph().isOpen()) {
		getGraph().clearEvents();
		getGraph().pollEvents();
		key = getGraph().getLastEvent();
		if (key == Arcade::Keys::ESC && _inMenu)
			return close();
		else
			swapLib(key);
		if (!_update(&menu, key))
			swapLib(Arcade::Keys::ESC);
	}
}

bool Arcade::Core::_initGraph(const std::string &graphLibName)
{
	std::shared_ptr<DLLoader> dl(new DLLoader(graphLibName));
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
	_graphsName.push_back(graphLibName);
	_graphs.push_back(o);
	return true;
}

bool Arcade::Core::_initGraphs(const std::string &graphLibName)
{
	LibAnalyzer l;
	if (graphLibName.size() > 0 && !_initGraph(graphLibName))
			return false;
	for (auto &lib : l.getGraphs())
		if (!_initGraph(GRAPH_FOLDER"/" + lib))
			return false;
	return true;
}

bool Arcade::Core::_initGames()
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

bool Arcade::Core::init(const std::string &graphLibName)
{	
	if (!_initGraphs(graphLibName) || !_initGames())
		return false;
	return true;
}

Arcade::IGraphicLib &Arcade::Core::getGraph()
{
	return *(_graphs[_libGraphIncrementer % _graphs.size()]);
}

Arcade::IGameLib &Arcade::Core::getGame()
{
	if (_games.size() == 0) {
		fprintf(stderr, "No game found\n");
		exit(84);
	}
	return *(_games[_libGameIncrementer % _games.size()]);
}
