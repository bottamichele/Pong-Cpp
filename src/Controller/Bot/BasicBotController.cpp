#include "BasicBotController.hpp"

namespace Pong {
	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	BasicBotController::BasicBotController(PlayerPosition playerPos, std::shared_ptr<Paddle> myPaddle, std::shared_ptr<Ball> ball) : Controller(playerPos, myPaddle) {
		m_Ball = ball;
	}

	/* ==================================================
	 * ================= METHOD update() ================
	 * ================================================== */
	void BasicBotController::update(float deltaTime) {
		//Is ball moving toward to me?
		if( (m_Ball->velocity.x > 0.f && m_Position==POSITION_Right) ||
			(m_Ball->velocity.x < 0.f && m_Position==POSITION_Left)) {
			
			if (m_Ball->position.y < m_MyPaddle->position.y - m_MyPaddle->getHeight() / 2)
				movePaddle(MOVE_Down);
			else if (m_Ball->position.y > m_MyPaddle->position.y + m_MyPaddle->getHeight() / 2)
				movePaddle(MOVE_Up);
			else
				movePaddle(MOVE_None);
		}
		else {
			movePaddle(MOVE_None);
		}
	}
}