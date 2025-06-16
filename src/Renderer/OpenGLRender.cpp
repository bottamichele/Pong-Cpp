#include "OpenGLRender.hpp"

#include <iostream>

namespace Pong {
	/* ==================================================
	 * ================= SHADER SOURCES =================
	 * ================================================== */

	static const char* vertexShaderSource =
		"#version 330 core \n"
		"layout (location = 0) in vec2 aPos;"
		"void main() { \n"
		"	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); \n"
		"}\0";

	static const char* fragmentShaderSource =
		"#version 330 core \n"
		"out vec4 color; \n"
		"void main() { \n"
		"	color = vec4(1.0, 1.0, 1.0, 1.0); \n"
		"}\0";

	/* ==================================================
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	OpenGLRender::OpenGLRender(GLADloadproc loader) {
		if (!gladLoadGLLoader(loader)) {
			std::cout << "Failed to load GLAD" << std::endl;
			
			__debugbreak();
		}

		m_Shader = std::make_unique<ShaderProgram>(vertexShaderSource, fragmentShaderSource);
	}

	/* ==================================================
	 * =================== DESTRUCTOR ===================
	 * ================================================== */
	OpenGLRender::~OpenGLRender() {
		for (unsigned int objectId : m_ObjectIds) {
			unsigned int vao = m_IdObj2vao.at(objectId);
			unsigned int vbo = m_IdObj2vbo.at(objectId);
			unsigned int ebo = m_IdObj2ebo.at(objectId);

			glDeleteBuffers(1, &ebo);
			glDeleteBuffers(1, &vbo);
			glDeleteVertexArrays(1, &vao);
		}
	}

	/* ==================================================
	 * =========== METHOD setResolutionUsed() ===========
	 * ================================================== */
	void OpenGLRender::setResolutionUsed(unsigned int width, unsigned int height) {
		m_WidthScreen = width;
		m_HeightScreen = height;
	}

	/* ==================================================
	 * ============== METHOD updatePaddle() =============
	 * ================================================== */
	void OpenGLRender::updatePaddle(Paddle& aPaddle) {
		unsigned int vao, vbo, ebo;

		//Does aPaddle have its buffer vao and vbo?
		if (m_IdObj2vao.find(aPaddle.getId()) != m_IdObj2vao.end()) {
			//Retrieve its buffers.
			vao = m_IdObj2vao.at(aPaddle.getId());
			vbo = m_IdObj2vbo.at(aPaddle.getId());
			ebo = m_IdObj2ebo.at(aPaddle.getId());
		}
		else {
			//Create buffers.
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			m_IdObj2vao.insert({ aPaddle.getId(), vao });
			m_IdObj2vbo.insert({ aPaddle.getId(), vbo });
			m_IdObj2ebo.insert({ aPaddle.getId(), ebo });
			m_ObjectIds.push_back(aPaddle.getId());
		}

		//Update paddle.
		float paddle[] = { 
			(aPaddle.position.x - aPaddle.getWidth()/2) / (m_WidthScreen/2), (aPaddle.position.y + aPaddle.getHeight()/2) / (m_HeightScreen/2),			//Top-left vertix.
			(aPaddle.position.x + aPaddle.getWidth()/2) / (m_WidthScreen/2), (aPaddle.position.y + aPaddle.getHeight()/2) / (m_HeightScreen/2),			//Top-right vertix.
			(aPaddle.position.x - aPaddle.getWidth()/2) / (m_WidthScreen/2), (aPaddle.position.y - aPaddle.getHeight()/2) / (m_HeightScreen/2),			//Bottom-left vertix.
			(aPaddle.position.x + aPaddle.getWidth()/2) / (m_WidthScreen/2), (aPaddle.position.y - aPaddle.getHeight()/2) / (m_HeightScreen/2)			//Bottom-right vertix.
		};

		unsigned int indices[] = {
			0, 1, 2,		//First triangle.
			2, 1, 3			//Second triangle.
		};
		
		glBindVertexArray(vao);
		
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(paddle), paddle, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
		
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}

	/* ==================================================
	 * =============== METHOD updateBall() ==============
	 * ================================================== */
	void OpenGLRender::updateBall(Ball& aBall) {
		unsigned int vao, vbo, ebo;

		//Does aBall have its buffer vao and vbo?
		if (m_IdObj2vao.find(aBall.getId()) != m_IdObj2vao.end()) {
			//Retrieve its buffers.
			vao = m_IdObj2vao.at(aBall.getId());
			vbo = m_IdObj2vbo.at(aBall.getId());
			ebo = m_IdObj2ebo.at(aBall.getId());
		}
		else {
			//Create buffers.
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);

			m_IdObj2vao.insert({ aBall.getId(), vao });
			m_IdObj2vbo.insert({ aBall.getId(), vbo });
			m_IdObj2ebo.insert({ aBall.getId(), ebo });
			m_ObjectIds.push_back(aBall.getId());
		}

		//Update ball.
		float ball[] = {
			(aBall.position.x - aBall.getRadius()/2) / (m_WidthScreen/2), (aBall.position.y + aBall.getRadius()/2) / (m_HeightScreen/2),			//Top-left vertix.
			(aBall.position.x + aBall.getRadius()/2) / (m_WidthScreen/2), (aBall.position.y + aBall.getRadius()/2) / (m_HeightScreen/2),			//Top-right vertix.
			(aBall.position.x - aBall.getRadius()/2) / (m_WidthScreen/2), (aBall.position.y - aBall.getRadius()/2) / (m_HeightScreen/2),			//Bottom-left vertix.
			(aBall.position.x + aBall.getRadius()/2) / (m_WidthScreen/2), (aBall.position.y - aBall.getRadius()/2) / (m_HeightScreen/2)			//Bottom-right vertix.
		};

		unsigned int indices[] = {
			0, 1, 2,		//First triangle.
			2, 1, 3			//Second triangle.
		};

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ball), ball, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}

	/* ==================================================
	 * ================= METHOD render() ================
	 * ================================================== */
	void OpenGLRender::render() {
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render all game objects.
		for (unsigned int objectId : m_ObjectIds) {
			unsigned int vao = m_IdObj2vao.at(objectId);
			//unsigned int ebo = m_IdObj2ebo.at(objectId);

			m_Shader->use();
			glBindVertexArray(vao);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}