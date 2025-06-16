/* =======================================================
 * PlayerController.hpp: A player controller for a paddle.
 * ======================================================= */
#pragma once

#include "Controller.hpp"
#include <GLFW/glfw3.h>

namespace Pong {
	/// <summary>
	/// A player controller that controls a paddle by a player.
	/// </summary>
	class PlayerController : public Controller {
		public:
			/// <summary>
			/// Create player controller for a paddle.
			/// </summary>
			/// <param name="playerPos">Position of player.</param>
			/// <param name="myPaddle">Paddle to control by player.</param>
			PlayerController(PlayerPosition playerPos, std::shared_ptr<Paddle> myPaddle, GLFWwindow* gameWindow);

			/// <summary>
			/// Update player controller.
			/// </summary>
			/// <param name="deltaTime">Delta time</param>
			void update(float deltaTime);
		private:
			GLFWwindow* mp_GameWindow;			//Game window.
	};
}