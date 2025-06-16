#include "Controller.hpp"

namespace Pong {
	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	Controller::Controller(PlayerPosition playerPos, std::shared_ptr<Paddle> myPaddle) {
		m_MyPaddle = myPaddle;
		m_Position = playerPos;
	}

	/* ==================================================
	 * =============== METHOD movePaddle() ==============
	 * ================================================== */
	void Controller::movePaddle(MovingType moveType) {
		switch (moveType) {
			case MOVE_Up: 
				{
					Vector2 upDir(0.f, 1.f);
					m_MyPaddle->velocity = Paddle::SPEED * upDir;
					break;
				}
			case MOVE_Down:
				{
					Vector2 downDir(0.f, -1.f);
					m_MyPaddle->velocity = Paddle::SPEED * downDir;
					break; 
				}
			case MOVE_None:
				m_MyPaddle->velocity = Vector2(0.f, 0.f);
				break;
		}
	}
}