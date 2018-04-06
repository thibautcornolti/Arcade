/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scoreboard.hpp
*/

#ifndef CPP_ARCADE_SCOREBOARD_HPP
#define CPP_ARCADE_SCOREBOARD_HPP

#include <vector>
#include <map>

#define SCOREBOARD "scores"

namespace Arcade {

	class Scoreboard {
		public:
			Scoreboard();
			~Scoreboard();

			void setGameName(const std::string &gameName);
			bool readScoreboard();
			std::map<const std::string, std::vector<std::string>> getScoreboard() const;


			size_t getScores() const;
			void addScores(const size_t&);
			void subScores(const size_t&);
			void resetScores();

		private:
			std::string _gameName;
			std::map<const std::string, std::vector<std::string>> _allScores;
			size_t _score = 0;
	};

}


#endif //CPP_ARCADE_SCOREBOARD_HPP
