/* =======================================================
 * GameObject.hpp: An abstraction of object game of Pong.
 * ======================================================= */
#pragma once

#include "Maths/Vector2.hpp"

namespace Pong {
	/// <summary>
	/// A game object of Pong game.
	/// </summary>
	class GameObject {
		public:
			GameObject();

			void update(float deltaTime);

			/// <summary>
			/// Returns id of this object.
			/// </summary>
			/// <returns>Object id</returns>
			inline unsigned int getId() const { return m_Id; };

			Vector2 position;							//Position of object.
			Vector2 velocity;							//Velocity of object.
		private:
			unsigned int m_Id;							//Object id.
	};
};