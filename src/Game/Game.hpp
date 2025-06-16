/* ==================================================
 * Game.hpp: Entry poiny of Pong game.
 * ================================================== */
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Renderer/OpenGLRender.hpp"
#include "Match.hpp"
#include "Objects/Field.hpp"
#include "Objects/Paddle.hpp"
#include "Objects/Ball.hpp"
#include "Controller/Controller.hpp"

namespace Pong {
	/// <summary>
	/// Pong game.
	/// </summary>
	class Game {
		public:
			/// <summary>
			/// Create an instance of Pong game.
			/// </summary>
			/// <param name="bFirstPlayerBot">true if you want that first player is a bot, false you do not.</param>
			/// <param name="bSecondPlayerBot">true if you want that second player is a bot, false you do not.</param>
			Game(bool bFirstPlayerBot, bool bSecondPlayerBot);
			~Game();

			/// <summary>
			/// Run Pong.
			/// </summary>
			void run();
		private:
			GLFWwindow* mp_Window;								//Game window.			
			std::unique_ptr<OpenGLRender> m_Render;				//Game render.
			float oldTime;										//Old time got by glfwGetTime().

			std::shared_ptr<Controller> m_FirstPlayer;			//First player of Pong game.
			std::shared_ptr<Controller> m_SecondPlayer;			//Second player of Pong game.
			std::unique_ptr<Match> m_Match;						//Match of Pong game.
			std::shared_ptr<Paddle> m_LeftPaddle;				//Paddle at left-side of field.
			std::shared_ptr<Paddle> m_RightPaddle;				//Paddle at right-side of field.
			std::shared_ptr<Ball> m_Ball;						//Ball.
			std::shared_ptr<Field> m_Field;						//Game field.

			/// <summary>
			/// Initialize the game.
			/// </summary>
			void init(bool bFirstPlayerBot, bool bSecondPlayerBot);

			/// <summary>
			/// Shutdown the game.
			/// </summary>
			void shutdown();

			/// <summary>
			/// Check collision of Pong objects.
			/// </summary>
			void checkCollisionObjects();

			void setPaddlesAndBall();
	};
}