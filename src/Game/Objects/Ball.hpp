/* ==================================================
 * Ball.hpp: Ball of Pong game.
 * ================================================== */
#pragma once

#include "GameObject.hpp"
#include "Paddle.hpp"

namespace Pong {
	/// <summary>
	/// A ball of Game pong.
	/// </summary>
	class Ball : public GameObject {
		public:
			/// <summary>
			/// Create ball
			/// </summary>
			/// <param name="radius">Radius of ball.</param>
			Ball(unsigned int radius);

			/// <summary>
			/// Return the radius of this ball.
			/// </summary>
			/// <returns>Radius of ball.</returns>
			inline unsigned int getRadius() const { return m_Radius; };

			/// <summary>
			/// Reset last paddle id collided by this ball.
			/// </summary>
			void resetLastPaddleIdCollided();

			/// <summary>
			/// Return last paddle id collided by this ball.
			/// </summary>
			/// <returns>Last paddle id collided.</returns>
			inline unsigned int getLastPaddleIdCollided() { return m_LastPaddleIdCollided; };

			/// <summary>
			/// Choose a random direction for this ball.
			/// </summary>
			void chooseRandomDirection();

			/// <summary>
			/// Check if ball collides aPaddle.
			/// </summary>
			/// <param name="aPaddle">Paddle to check if it is collided</param>
			/// <returns>true if ball collides aPaddle, false otherwise.</returns>
			bool checkCollision(Paddle& aPaddle);

			/// <summary>
			/// Check if ball collides at a point.
			/// </summary>
			/// <param name="aPoint">Point to check if collide.</param>
			/// <returns>true if ball collide aPoint, false otherwise.</returns>
			bool checkCollisionPoint(const Vector2& aPoint);

			/// <summary>
			/// Check if ball collides at a point 
			/// </summary>
			/// <param name="x">x of point</param>
			/// <param name="y">y of point.</param>
			/// <returns>true if ball collides that point, false otherwise.</returns>
			inline bool checkCollisionPoint(float x, float y) {
				return checkCollisionPoint(Vector2(x, y));
			}

			static const float SPEED;					//Speed of ball.
		private:
			unsigned int m_Radius;						//Radius of ball.
			unsigned int m_LastPaddleIdCollided;		//Last paddle collided by this ball.
	};
};