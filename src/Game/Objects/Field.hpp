/* ==================================================
 * Field.hpp: Game field of Pong.
 * ================================================== */
#pragma once

#include "GameObject.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

namespace Pong {
	/// <summary>
	/// Game field.
	/// </summary>
	class Field : public GameObject {
		public:
			/// <summary>
			/// Collision type at a object.
			/// </summary>
			enum CollisionType {
				COLLIDE_None,		//Field is not collided by an object.
				COLLIDE_Top,		//Field is collided at top by an object. 
				COLLIDE_Right,		//Field is collided at right by an object.
				COLLIDE_Down,		//Field is collided at down by an object.
				COLLIDE_Left		//Field is collided at left by an object.
			};

			/// <summary>
			/// Create game field.
			/// </summary>
			/// <param name="width">Width of field.</param>
			/// <param name="height">Height of field.</param>
			Field(int width, int height);

			/// <summary>
			/// Return width of game field.
			/// </summary>
			/// <returns>Width of field.</returns>
			inline int getWidth() { return m_Width; }

			/// <summary>
			/// Return height of game field.
			/// </summary>
			/// <returns>Height of field.</returns>
			inline int getHeight() { return m_Height; }

			/// <summary>
			/// Check if aPaddle collides the border of field.
			/// </summary>
			/// <param name="aPaddle">Collision type at border.</param>
			/// <returns></returns>
			CollisionType checkBorderCollision(Paddle& aPaddle);

			/// <summary>
			/// Check if aBall collides the border of field.
			/// </summary>
			/// <param name="aBall">Collision type at border.</param>
			/// <returns></returns>
			CollisionType checkBorderCollision(Ball& aBall);
		private:
			int m_Width;			//Width of field.
			int m_Height;			//Height of field.
	};
}
