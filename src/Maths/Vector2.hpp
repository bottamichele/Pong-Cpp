/* ==================================================
 * Vector2.hpp: Bidimensional vector.
 * ================================================== */
#pragma once

namespace Pong {
	/// <summary>
	/// A bidimensional vector.
	/// </summary>
	class Vector2 {
		public:
			//Attributes.
			float x;		//Axis x.
			float y;		//Axis y.

			//Methods.

			/// <summary>
			/// Create vector bidimensional at position (x, y).
			/// </summary>
			/// <param name="inX">X value.</param>
			/// <param name="inY">Y value.</param>
			Vector2(float x, float y);

			/// <summary>
			/// Create vector bidimensional at position (0, 0).
			/// </summary>
			Vector2();

			/// <summary>
			/// Calculate magnitude of this vector.
			/// </summary>
			/// <returns>Magnitude of this vector.</returns>
			float magnitude();

			/// <summary>
			/// Return the unitary vector of this vector.
			/// </summary>
			/// <returns>Unitary vector of this vector.</returns>
			Vector2 normal();

			/// <summary>
			/// Sum of two vectors.
			/// </summary>
			/// <param name="other">Vector to sum.</param>
			/// <returns>Sum result of this vector and other.</returns>
			Vector2 operator+(const Vector2& other);

			/// <summary>
			/// Suvtraction of two vectors.
			/// </summary>
			/// <param name="other">Vector to subtract.</param>
			/// <returns>Subtraction result of this vector and other.</returns>
			Vector2 operator-(const Vector2& other);

			/// <summary>
			/// Multiplication between a vector and a number.
			/// </summary>
			/// <param name="num">Number to multiply.</param>
			/// <returns>Multiplication result of this vector and num.</returns>
			Vector2 operator*(float num);

			/// <summary>
			/// Multiplication between num and vect.
			/// </summary>
			/// <param name="num">Number to mutiply.</param>
			/// <param name="vect">Vector to multiply.</param>
			/// <returns>Multiplication result of sum and vect</returns>
			friend Vector2 operator*(float num, const Vector2& vect) {
				Vector2 result;

				result.x = num * vect.x;
				result.y = num * vect.y;
				return result;
			}

			/// <summary>
			/// Dot product.
			/// </summary>
			/// <param name="other">Other vector for dot product.</param>
			/// <returns>The result of dot product</returns>
			float dot(const Vector2& other);

			/// <summary>
			/// Sum other to this vector.
			/// </summary>
			/// <param name="other">Vector to sum</param>
			/// <returns>Sum result at this vector.</returns>
			Vector2& operator+=(const Vector2& other);

			/// <summary>
			/// Subtract other to this vector.
			/// </summary>
			/// <param name="other">Vector to subtract</param>
			/// <returns>Subtract result at this vector.</returns>
			Vector2& operator-=(const Vector2& other);
	};
};