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

/*!
 * @namespace Arcade
 * @brief Arcade project namespace
 */
namespace Arcade {

	/*!
	 * @class Scoreboard
	 * @brief Scoreboard class
	 *
	 * Class used to manage the scoreboard
	 *
	 */
	class Scoreboard {
	public:
		/*!
		 * @brief Scoreboard class's constructor
		 *
		 * Creates a new scoreboard class instance.
		 *
		 */
		Scoreboard();

		/*!
		 * @brief Scoreboard class's destructor
		 */
		~Scoreboard();

		/*!
		 * @brief Scoreboard game name's setter
		 */
		void setGameName(const std::string &gameName);

		/*!
		 * @brief Scoreboard player name's setter
		 */
		void setPlayerName(const std::string &playerName);

		/*!
		 * @brief Scoreboard initializer
		 * 
		 * Reads the file to feed itself.
		 * 
		 */
		bool readScoreboard();

		/*!
		 * @brief Scoreboard last player score's getter
		 * @return the score of the last player as a size_t
		 */
		size_t getLastPlayerScore();

		/*!
		 * @brief Scoreboard getter
		 * @return all the scoreboard.
		 */
		std::map<std::string, std::vector<std::string>> getScoreboard() const;

		/*!
		 * @brief Scoreboard current score's getter
		 * @return the current score.
		 */
		size_t getScores() const;

		/*!
		 * @brief Scoreboard setter
		 * 
		 * Add score to the current score.
		 * 
		 */
		void addScores(const size_t&);

		/*!
		 * @brief Scoreboard setter
		 * 
		 * Sub score to the current score.
		 * 
		 */
		void subScores(const size_t&);

		/*!
		 * @brief Scoreboard reseter
		 * 
		 * Reset the scores.
		 * 
		 */
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
