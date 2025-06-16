#include "Vector2.hpp"
#include <cmath>

namespace Pong {
	/* ==================================================
	 * ================== CONSTRUCTORS ==================
	 * ================================================== */
	Vector2::Vector2(float inX, float inY) : x(inX), y(inY) {};

	Vector2::Vector2() : x(0.f), y(0.f) {};
	
	/* ==================================================
	 * ================= MATH OPERATIONS ================
	 * ================================================== */
	
	/* ---------- Magnitude operation ---------- */
	float Vector2::magnitude() {
		return sqrt(x * x + y * y);
	}

	/* ---------- Normal operation ---------- */
	Vector2 Vector2::normal() {
		if(x == 0.f && y == 0.f)	return Vector2(0.f, 0.f);
		
		float magnitude = this->magnitude();
		return (1.f/magnitude) * *this;
	}

	/* ---------- Sum operations ---------- */
	Vector2 Vector2::operator+(const Vector2& other) {
		Vector2 result;
		result.x = this->x + other.x;
		result.y = this->y + other.y;

		return result;
	}

	Vector2& Vector2::operator+=(const Vector2& other) {
		this->x += other.x;
		this->y += other.y;

		return *this;
	}

	/* ---------- Subtraction operations ---------- */
	Vector2 Vector2::operator-(const Vector2& other) {
		Vector2 result;
		result.x = this->x - other.x;
		result.y = this->y - other.y;

		return result;
	}

	Vector2& Vector2::operator-=(const Vector2& other) {
		this->x -= other.x;
		this->y -= other.y;

		return *this;
	}

	/* ---------- Multiplication operation ---------- */
	Vector2 Vector2::operator*(float num) {
		Vector2 result;
		result.x = this->x * num;
		result.y = this->y * num;

		return result;
	}

	/* ---------- Dot product ---------- */
	float Vector2::dot(const Vector2& other) {
		return this->x * other.x + this->y * other.y;
	}
}