/* =======================================================
 * Controller.hpp: An abstraction controller for a paddle.
 * ======================================================= */
#pragma once

#include "Game/Objects/Paddle.hpp"
#include <memory>

namespace Pong {
	enum PlayerPosition {
		POSITION_Left,
		POSITION_Right
	};

	/// <summary>
	/// This is an abstract class and is a base of paddle controlled by player or bot.
	/// </summary>
	class Controller {
		public:
			/// <summary>
			/// Create a controller for a paddle
			/// </summary>
			/// <param name="playerPos">Position of player.</param>
			/// <param name="myPaddle">Paddle to control.</param>
			Controller(PlayerPosition playerPos, std::shared_ptr<Paddle> myPaddle);

			/// <summary>
			/// Update the controller.
			/// </summary>
			/// <param name="deltaTime">Delta time from last update time and this update time.</param>
			virtual void update(float deltaTime) = 0;

			/// <summary>
			/// Return paddle id of this controller.
			/// </summary>
			/// <returns>Paddle if of controller.</returns>
			inline unsigned int getPaddleId() { return m_MyPaddle->getId(); };
		protected:
			std::shared_ptr<Paddle> m_MyPaddle;					//Paddle controlled by player or bot.
			PlayerPosition m_Position;							//Position of player.
			
			enum MovingType {
				MOVE_None	= 0,		//Paddle is not moved.
				MOVE_Up		= 1,		//Paddle is moved toward up.
				MOVE_Down	= 2			//Paddle is moved toward down.
			};
			
			/// <summary>
			/// Move paddle.
			/// </summary>
			/// <param name="moveType">Move type.</param>
			void movePaddle(MovingType moveType);
	};
}