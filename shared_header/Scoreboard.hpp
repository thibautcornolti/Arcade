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
			void setPlayerName(const std::string &playerName);

			bool readScoreboard();
			size_t getLastPlayerScore();
			std::map<std::string, std::vector<std::string>> getScoreboard() const;

			size_t getScores() const;
			void addScores(const size_t&);
			void subScores(const size_t&);
			void resetScores();

		private:
			std::string _gameName;
			std::string _playerName = "Unknown";
			std::map<std::string, std::vector<std::string>> _allScores;
			std::map<std::string, std::vector<std::pair<std::string, size_t>>> _allScoresComputed;
			size_t _score = 0;
	};

}


#endif //CPP_ARCADE_SCOREBOARD_HPP
