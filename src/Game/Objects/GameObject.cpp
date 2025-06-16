#include "GameObject.hpp"

namespace Pong {
	static unsigned int idCount = 1;

	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	GameObject::GameObject() {
		m_Id = idCount;
		idCount++;
	}

	/* ==================================================
	 * ================= METHOD update() ================
	 * ================================================== */
	void GameObject::update(float deltaTime) {
		position += velocity * deltaTime;
	}
}