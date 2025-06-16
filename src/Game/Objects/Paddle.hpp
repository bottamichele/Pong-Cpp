/* ==================================================
 * Paddle.hpp: Paddle of a player.
 * ==================================================*/
#pragma once

#include "GameObject.hpp"

namespace Pong {
	/// <summary>
	/// A paddle of Pong game.
	/// </summary>
	class Paddle : public GameObject {
		public:
			/// <summary>
			/// Create paddle.
			/// </summary>
			/// <param name="width">Width of paddle.</param>
			/// <param name="height">Height of paddle.</param>
			Paddle(int width, int height);

			/// <summary>
			/// Return width of this paddle.
			/// </summary>
			/// <returns>Width of paddle.</returns>
			inline int getWidth() const { return m_Width; };

			/// <summary>
			/// Return height of this paddle.
			/// </summary>
			/// <returns>Height of paddle.</returns>
			inline int getHeight() const { return m_Height; };

			/// <summary>
			/// Check if paddle collides at a point.
			/// </summary>
			/// <param name="aPoint">Point to check if collide.</param>
			/// <returns>true if paddle collides aPoint, false otherwise.</returns>
			bool checkCollisionPoint(const Vector2& aPoint);

			/// <summary>
			/// Check if paddle collides at a point 
			/// </summary>
			/// <param name="x">x of point</param>
			/// <param name="y">y of point.</param>
			/// <returns>true if paddle collides that point, false otherwise.</returns>
			inline bool checkCollisionPoint(float x, float y) {
				return checkCollisionPoint(Vector2(x, y));
			}

			static const float SPEED;		//Speed of paddle.
		private:
			int m_Width;					//Width of paddle.
			int m_Height;					//Height of paddle.
	};
}