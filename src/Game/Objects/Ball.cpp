#include "Ball.hpp"

#include <cmath>
#include <chrono>
#include <random>

namespace Pong {
	const float Ball::SPEED = 450.f;

	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	Ball::Ball(unsigned int radius) : m_Radius(radius) {
		m_LastPaddleIdCollided = 0;
	}

	/* ==================================================
	 * ======= METHOD resetLastPaddleIdCollided() =======
	 * ================================================== */
	void Ball::resetLastPaddleIdCollided() {
		m_LastPaddleIdCollided = 0;
	}

	/* ==================================================
	 * ========= METHOD chooseRandomDirection() =========
	 * ================================================== */
	void Ball::chooseRandomDirection() {
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::uniform_real_distribution<float> distribution(0.f, 1.f);

		float y = distribution(generator) / 2;
		float x = sqrt(1 - y * y);

		x = distribution(generator) <= 0.5f ? x : -x;
		y = distribution(generator) <= 0.5f ? y : -y;
		velocity = Ball::SPEED * Vector2(x, y);
	}

	/* ==================================================
	 * ============= METHOD checkCollision() ============
	 * ================================================== */
	bool Ball::checkCollision(Paddle& aPaddle) {
		//Ball vertices.
		Vector2 topLeft(position.x - m_Radius/2, position.y + m_Radius/2);			//Top-left vertix.
		Vector2 topRight(position.x + m_Radius/2, position.y + m_Radius/2);			//Top-right vertix.
		Vector2 bottomLeft(position.x - m_Radius/2, position.y - m_Radius/2);		//Bottom-left vertix.
		Vector2 bottomRight(position.x + m_Radius/2, position.y - m_Radius/2);		//Bottim-right vertix.

		if (aPaddle.checkCollisionPoint(topLeft) || aPaddle.checkCollisionPoint(topRight) || aPaddle.checkCollisionPoint(bottomLeft) || aPaddle.checkCollisionPoint(bottomRight)) {
			m_LastPaddleIdCollided = aPaddle.getId();
			return true;
		}
		else {
			return false;
		}
	}

	/* ==================================================
	 * ========== METHOD checkCollisionPoint() ==========
	 * ================================================== */
	bool Ball::checkCollisionPoint(const Vector2& aPoint) {
		//Ball vertices.
		Vector2 topLeft(position.x - m_Radius/2, position.y + m_Radius/2);			//Top-left vertix.
		Vector2 topRight(position.x + m_Radius/2, position.y + m_Radius/2);			//Top-right vertix.
		Vector2 bottomLeft(position.x - m_Radius/2, position.y - m_Radius/2);		//Bottom-left vertix.
		Vector2 bottomRight(position.x + m_Radius/2, position.y - m_Radius/2);		//Bottim-right vertix.

		return	(topLeft.x <= aPoint.x		&& aPoint.y <= topLeft.y)		&&
				(aPoint.x <= topRight.x		&& aPoint.y <= topRight.y)		&&
				(bottomLeft.x <= aPoint.x	&& bottomLeft.y <= aPoint.y)	&&
				(aPoint.x <= bottomRight.x	&& bottomRight.y <= aPoint.y);
	}
}