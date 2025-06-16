/* ============================================================
 * BasicBotController.hpp: A basic bot controller for a paddle.
 * ============================================================ */
#pragma once

#include "Controller/Controller.hpp"
#include "Game/Objects/Ball.hpp"

namespace Pong {
	/// <summary>
	/// A basic bot controller for paddle.
	/// </summary>
	class BasicBotController : public Controller {
		public:
			/// <summary>
			/// Create basic bot controller.
			/// </summary>
			/// <param name="playerPos">Position of paddle</param>
			/// <param name="myPaddle">Paddle to control</param>
			/// <param name="ball">Ball</param>
			BasicBotController(PlayerPosition playerPos, std::shared_ptr<Paddle> myPaddle, std::shared_ptr<Ball> ball);

			void update(float deltaTime);
		private:
			std::shared_ptr<Ball> m_Ball;			//Ball of Pong game.
	};
}


