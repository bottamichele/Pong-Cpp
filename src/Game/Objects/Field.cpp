#include "Field.hpp"

namespace Pong {
	/* ==================================================
	 * =================== COSTRUCTOR ===================
	 * ================================================== */
	Field::Field(int width, int height) : m_Width(width), m_Height(height), GameObject() {
		position = Vector2();
	}

	/* ================================================== 
	 * ========= METHOD checkBorderCollision() ==========
	 * ================================================== */
	Field::CollisionType Field::checkBorderCollision(Paddle& aPaddle) {
		Vector2 top(aPaddle.position.x, m_Height/2);
		Vector2 bottom(aPaddle.position.x, -m_Height/2);

		if (aPaddle.checkCollisionPoint(top))
			return COLLIDE_Top;
		else if (aPaddle.checkCollisionPoint(bottom))
			return COLLIDE_Down;
		else
			return COLLIDE_None;
	}

	Field::CollisionType Field::checkBorderCollision(Ball& aBall) {
		Vector2 top(aBall.position.x, m_Height/2);
		Vector2 bottom(aBall.position.x, -m_Height/2);
		Vector2 right(m_Width/2, aBall.position.y);
		Vector2 left(-m_Width/2, aBall.position.y);

		if (aBall.checkCollisionPoint(top))
			return COLLIDE_Top;
		else if (aBall.checkCollisionPoint(bottom))
			return COLLIDE_Down;
		else if (aBall.checkCollisionPoint(right))
			return COLLIDE_Right;
		else if (aBall.checkCollisionPoint(left))
			return COLLIDE_Left;
		else
			return COLLIDE_None;
	}
}