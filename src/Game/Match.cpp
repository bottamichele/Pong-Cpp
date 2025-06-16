#include "Match.hpp"

namespace Pong {
	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	Match::Match(std::shared_ptr<Controller> firstPlayer, std::shared_ptr<Controller> secondPlayer, unsigned int goalScore) {
		m_FirstPlayer = firstPlayer;
		m_ScoreFirstPlayer = 0;

		m_SecondPlayer = secondPlayer;
		m_ScoreSecondPlayer = 0;

		m_GoalScore = goalScore;
	}

	/* ==================================================
	 * ============= METHOD assignPointAt() =============
	 * ================================================== */
	void Match::assignPointAt(Controller& aPlayer) {
		if (aPlayer.getPaddleId() == m_FirstPlayer->getPaddleId()) {
			m_ScoreFirstPlayer++;
		}
		else if (aPlayer.getPaddleId() == m_SecondPlayer->getPaddleId()) {
			m_ScoreSecondPlayer++;
		}
	}

	/* ==================================================
	 * ================ METHOD getScore() ===============
	 * ================================================== */
	unsigned int Match::getScore(Controller& aPlayer) {
		unsigned int score = 0;

		if (aPlayer.getPaddleId() == m_FirstPlayer->getPaddleId()) {
			score = m_ScoreFirstPlayer;
		}
		else if (aPlayer.getPaddleId() == m_SecondPlayer->getPaddleId()) {
			score = m_ScoreSecondPlayer;
		}

		return score;
	}

	/* ==================================================
	 * ================ METHOD isEnded() ================
	 * ================================================== */
	bool Match::isEnded() {
		return (m_ScoreFirstPlayer == m_GoalScore) || (m_ScoreSecondPlayer == m_GoalScore);
	}
}