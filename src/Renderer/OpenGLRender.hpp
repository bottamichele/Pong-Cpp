/* ==================================================
 * OpenGLRender.hpp: Open GL Renderer for Pong game. 
 * ================================================== */
#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include <glad/glad.h>

#include "ShaderProgram.hpp"

#include "Game/Objects/Ball.hpp"
#include "Game/Objects/Paddle.hpp"

namespace Pong {
	/// <summary>
	/// OpenGL Render for Pong
	/// </summary>
	class OpenGLRender {
		public:
			OpenGLRender(GLADloadproc loader);

			~OpenGLRender();

			/// <summary>
			/// Set what resolution screen is used.
			/// </summary>
			/// <param name="width">Width of screen.</param>
			/// <param name="height">Height of screen.</param>
			void setResolutionUsed(unsigned int width, unsigned int height);

			/// <summary>
			/// Update a paddle.
			/// </summary>
			/// <param name="aPaddle">A paddle to update.</param>
			void updatePaddle(Paddle& aPaddle);

			/// <summary>
			/// Update a ball.
			/// </summary>
			/// <param name="aBall">A ball to update.</param>
			void updateBall(Ball& aBall);

			/// <summary>
			/// Render all obects and its updates.
			/// </summary>
			void render();
		private:
			unsigned int m_WidthScreen;							//Width of screen.
			unsigned int m_HeightScreen;						//Height of screen.
			std::unique_ptr<ShaderProgram> m_Shader;			//Program shader used into OpenGL render of Pong game.
			std::vector<unsigned int> m_ObjectIds;
			std::unordered_map<unsigned int, unsigned int> m_IdObj2vao;
			std::unordered_map<unsigned int, unsigned int> m_IdObj2vbo;
			std::unordered_map<unsigned int, unsigned int> m_IdObj2ebo;
	};
}