/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scoreboard.hpp
*/

#ifndef CPP_ARCADE_SCOREBOARD_HPP
#define CPP_ARCADE_SCOREBOARD_HPP

#include <vector>

#define SCOREBOARD "../../scores"

namespace Arcade {

	class Scoreboard {
		public:
			Scoreboard(const std::string&);
			~Scoreboard();

			std::vector<std::pair<std::string, size_t>> readScores() const;

			std::vector<std::pair<std::string, size_t>> getScoreboard() const;
			void addPlayerToScoreboard(int);
			void updateScoreboard();
			size_t getScores() const;
			void addScores(const size_t&);
			void removeScores(const size_t&);

		private:
			const std::string _gameName;
			std::vector<std::pair<std::string, size_t>> _scores = {{"Unknown", 0}};
			size_t _score;
	};

}


#endif //CPP_ARCADE_SCOREBOARD_HPP
