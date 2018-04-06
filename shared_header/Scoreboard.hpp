/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scoreboard.hpp
*/

#ifndef CPP_ARCADE_SCOREBOARD_HPP
#define CPP_ARCADE_SCOREBOARD_HPP

#include <vector>

#define SCOREBOARD "scores"

namespace Arcade {

	class Scoreboard {
		public:
			Scoreboard(const std::string&, const std::string&);
			~Scoreboard();

			std::vector<std::pair<std::string, size_t>> getScoreboard() const;
			void saveScoreboard();
			size_t getScores() const;
			void addScores(const size_t&);
			void subScores(const size_t&);
			void resetScores();

		private:
			void readScores();
			std::string getFormattedScoreboard() const;
			void addPlayerToScoreboard(int);
			void updateScoreboard();

		private:
			const std::string _gameName;
			const std::string _playerName;
			std::vector<std::pair<std::string, size_t>> _scores = {{"Unknown", 0}};
			size_t _score = 0;
	};

}


#endif //CPP_ARCADE_SCOREBOARD_HPP
