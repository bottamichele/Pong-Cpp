/* ==================================================
 * Match.hpp: Information about of current match.
 * ================================================== */
#pragma once

#include "Controller/Controller.hpp"

namespace Pong {
	class Match {
		public:
			Match(std::shared_ptr<Controller> firstPlayer, std::shared_ptr<Controller> secondPlayer, unsigned int goalScore);

			/// <summary>
			/// Assign a point at a player
			/// </summary>
			/// <param name="aPlayer">Player to assign a point.</param>
			void assignPointAt(Controller& aPlayer);

			/// <summary>
			/// Return the score of a player.
			/// </summary>
			/// <param name="player">Player to get its score.</param>
			/// <returns>Score of player</returns>
			unsigned int getScore(Controller& player);

			/// <summary>
			/// Return goal score of match.
			/// </summary>
			/// <returns>Goal score of match.</returns>
			inline unsigned int getGoalScore() { return m_GoalScore; };

			/// <summary>
			/// Check if match is ended.
			/// </summary>
			/// <returns>true if match is ended, false otherwise.</returns>
			bool isEnded();
		private:
			std::shared_ptr<Controller> m_FirstPlayer;				//First player.
			std::shared_ptr<Controller> m_SecondPlayer;				//Second player.
			unsigned int m_ScoreFirstPlayer;						//Score of first player.
			unsigned int m_ScoreSecondPlayer;						//Score of second player.
			unsigned int m_GoalScore;								//Goal score of match.
	};
}
