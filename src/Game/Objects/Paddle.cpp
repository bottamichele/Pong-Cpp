#include "Paddle.hpp"

namespace Pong {
	const float Paddle::SPEED = 300.f;

	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	Paddle::Paddle(int width, int height) : m_Width(width), m_Height(height) {};

	/* ==================================================
	 * ========== METHOD checkCollisionPoint() ==========
	 * ================================================== */
	bool Paddle::checkCollisionPoint(const Vector2& aPoint) {
		//Paddle vertices.
		Vector2 topLeft(position.x - m_Width/2, position.y + m_Height/2);			//Top-left vertix.
		Vector2 topRight(position.x + m_Width/2, position.y + m_Height/2);			//Top-right vertix.
		Vector2 bottomLeft(position.x - m_Width/2, position.y - m_Height/2);		//Bottom-left vertix.
		Vector2 bottomRight(position.x + m_Width/2, position.y - m_Height/2);		//Bottim-right vertix.

		return	(topLeft.x <= aPoint.x		&& aPoint.y <= topLeft.y)		&&
				(aPoint.x <= topRight.x		&& aPoint.y <= topRight.y)		&&
				(bottomLeft.x <= aPoint.x	&& bottomLeft.y <= aPoint.y)	&&
				(aPoint.x <= bottomRight.x	&& bottomRight.y <= aPoint.y);
	}
}