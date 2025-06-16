#include "PlayerController.hpp"

namespace Pong {
	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	PlayerController::PlayerController(PlayerPosition playerPos, std::shared_ptr<Paddle> myPaddle, GLFWwindow* gameWindow) : Controller(playerPos, myPaddle) {
		mp_GameWindow = gameWindow;
	}

	/* ==================================================
	 * ================= METHOD update() ================
	 * ================================================== */
	void PlayerController::update(float deltaTime) {
		if ( ((glfwGetKey(mp_GameWindow, GLFW_KEY_UP) == GLFW_PRESS) && (m_Position == POSITION_Left))	 ||
			 ((glfwGetKey(mp_GameWindow, GLFW_KEY_W) == GLFW_PRESS)	 && (m_Position == POSITION_Right))) {
			
			movePaddle(MOVE_Up);
		}
		else if ( ((glfwGetKey(mp_GameWindow, GLFW_KEY_DOWN) == GLFW_PRESS) && (m_Position == POSITION_Left))	|| 
				  ((glfwGetKey(mp_GameWindow, GLFW_KEY_S) == GLFW_PRESS)	&& (m_Position == POSITION_Right))) {
			
			movePaddle(MOVE_Down);
		}
		else {
			movePaddle(MOVE_None);
		}
	}
}