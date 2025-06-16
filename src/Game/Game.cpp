#include "Game.hpp"

#include <iostream>
#include <math.h>

#include "Controller/PlayerController.hpp"
#include "Controller/Bot/BotControllerFactory.hpp"

namespace Pong {
	//Screen properties.
	static const int WIDTH_SCREEN = 800;
	static const int HEIGHT_SCREEN = 600;

	//Paddle properties.
	static const int WIDTH_PADDLE = 10;
	static const int HEIGHT_PADDLE = 80;

	//Ball property.
	static const int RADIUS_BALL = 10;

	static const int GOAL_SCORE = 11;

	/* ================================================== 
	 * =================== CONSTRUCTOR ==================
	 * ================================================== */
	Game::Game(bool bFirstPlayerBot, bool bSecondPlayerBot) {
		init(bFirstPlayerBot, bSecondPlayerBot);
	}

	/* ==================================================
	 * =================== DESTRUCTOR ===================
	 * ================================================== */
	Game::~Game() {
		shutdown();
	}

	/* ==================================================
	 * ================== METHOD init() =================
	 * ================================================== */
	void Game::init(bool bFirstPlayerBot, bool bSecondPlayerBot) {
		//Initialize GLFW.
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		//Create GLFW window.
		mp_Window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "Pong", nullptr, nullptr);
		if (!mp_Window) {
			std::cout << "Failed to create window!" << std::endl;
			__debugbreak();
		}
		glfwMakeContextCurrent(mp_Window);
		//glfwSetFramebufferSizeCallback(mp_Window, [](GLFWwindow* window, int width, int height) {
		//	glViewport(0, 0, width, height);
		//});

		//Create renderer.
		m_Render = std::make_unique<OpenGLRender>((GLADloadproc)glfwGetProcAddress);
		m_Render->setResolutionUsed(WIDTH_SCREEN, HEIGHT_SCREEN);

		//Create Pong's objects.
		m_Field = std::make_shared<Field>(WIDTH_SCREEN, HEIGHT_SCREEN);
		m_LeftPaddle = std::make_shared<Paddle>(WIDTH_PADDLE, HEIGHT_PADDLE);
		m_RightPaddle = std::make_shared<Paddle>(WIDTH_PADDLE, HEIGHT_PADDLE);
		m_Ball = std::make_shared<Ball>(RADIUS_BALL);
		setPaddlesAndBall();

		//Create players.
		BotControllerFactoryInformation data = { m_Field, m_LeftPaddle, m_RightPaddle, m_Ball };

		if (bFirstPlayerBot) {
			data.positionPlayer = POSITION_Left;
			m_FirstPlayer = BotControllerFactory::create(data);
		}
		else {
			m_FirstPlayer = std::make_shared<PlayerController>(POSITION_Left, m_LeftPaddle, mp_Window);
		}
			
		if (bSecondPlayerBot) {
			data.positionPlayer = POSITION_Right;
			m_SecondPlayer = BotControllerFactory::create(data);
		}
		else {
			m_SecondPlayer = std::make_shared<PlayerController>(POSITION_Right, m_RightPaddle, mp_Window);
		}

		//Create match info.
		m_Match = std::make_unique<Match>(m_FirstPlayer, m_SecondPlayer, GOAL_SCORE);
		
		//Set other stuff.
		oldTime = 0.f;
		glfwSwapInterval(1);				//V-Sync enabled.
	}

	/* ==================================================
	 * ================ METHOD shutdown() ===============
	 * ================================================== */
	void Game::shutdown() {
		glfwTerminate();
	}

	/* ==================================================
	 * =========== METHOD setPaddlesAndBall() ===========
	 * ================================================== */
	void Game::setPaddlesAndBall() {
		m_LeftPaddle->position = Vector2(-0.975f * WIDTH_SCREEN / 2, 0.f);
		m_RightPaddle->position = Vector2(0.975f * WIDTH_SCREEN / 2, 0.f);

		m_Ball->position = Vector2(0.f, 0.f);
		m_Ball->chooseRandomDirection();
		m_Ball->resetLastPaddleIdCollided();
	}

	/* ==================================================
	 * ========= METHOD checkCollisionObjects() =========
	 * ================================================== */
	void Game::checkCollisionObjects() {
		Field::CollisionType collisionBallAndField = m_Field->checkBorderCollision(*m_Ball);

		//Does ball collide leftside or rightside of game field?
		if ((collisionBallAndField == Field::COLLIDE_Left) || (collisionBallAndField == Field::COLLIDE_Right)) {
			unsigned int lastPaddleCollided = m_Ball->getLastPaddleIdCollided();

			if (m_FirstPlayer->getPaddleId() == lastPaddleCollided)
				m_Match->assignPointAt(*m_FirstPlayer);
			else if (m_SecondPlayer->getPaddleId() == lastPaddleCollided)
				m_Match->assignPointAt(*m_SecondPlayer);

			setPaddlesAndBall();

			if (lastPaddleCollided > 0) {
				/* ---------- Diplay player scores. ---------- */
				int scoreFirstPlayer = m_Match->getScore(*m_FirstPlayer);
				int scoreSecondPlayer = m_Match->getScore(*m_SecondPlayer);

				std::cout << "P1: " << scoreFirstPlayer << "   -   " << scoreSecondPlayer << " :P2" << std::endl;
			}
		}
		else {
			//Does ball collide upside or downside of window?
			if (collisionBallAndField != Field::COLLIDE_None) {
				m_Ball->velocity = Vector2(m_Ball->velocity.x, -m_Ball->velocity.y);

				float distance = 0.f;
				if (collisionBallAndField == Field::COLLIDE_Top)
					distance = abs( HEIGHT_SCREEN/2 - (m_Ball->position.y + m_Ball->getRadius()/2) ) * -1;
				else
					distance = abs( -HEIGHT_SCREEN/2 - (m_Ball->position.y - m_Ball->getRadius()/2) );
				m_Ball->position += Vector2(0.f, distance);
			}

			//Does ball collides the first paddle?
			if (m_Ball->checkCollision(*m_LeftPaddle)) {
				Vector2 direction = (Vector2(-m_Ball->velocity.x, m_Ball->velocity.y) + 0.2f * m_LeftPaddle->velocity).normal();
				m_Ball->velocity = Ball::SPEED * direction;

				float distance = abs( (m_LeftPaddle->position.x + m_LeftPaddle->getWidth()/2) - (m_Ball->position.x - m_Ball->getRadius()/2) );
				m_Ball->position += Vector2(distance, 0.f);
			}
			//Does ball collides the second paddle?
			else if (m_Ball->checkCollision(*m_RightPaddle)) {
				Vector2 direction = (Vector2(-m_Ball->velocity.x, m_Ball->velocity.y) + 0.2f * m_RightPaddle->velocity).normal();
				m_Ball->velocity = Ball::SPEED * direction;

				float distance = abs( (m_RightPaddle->position.x - m_LeftPaddle->getWidth()/2) - (m_Ball->position.x + m_Ball->getRadius()/2) );
				m_Ball->position -= Vector2(distance, 0.f);
			}

			//Does the first paddle collide upside or downside of game field?
			Field::CollisionType collision_LeftPaddle_Field = m_Field->checkBorderCollision(*m_LeftPaddle);

			if (collision_LeftPaddle_Field != Field::COLLIDE_None) {
				m_LeftPaddle->velocity = Vector2();

				if(collision_LeftPaddle_Field == Field::COLLIDE_Top)
					m_LeftPaddle->position = Vector2(m_LeftPaddle->position.x, m_Field->getHeight()/2 - m_LeftPaddle->getHeight()/2);
				else
					m_LeftPaddle->position = Vector2(m_LeftPaddle->position.x, -m_Field->getHeight()/2 + m_LeftPaddle->getHeight()/2);
			}

			//Does the second paddle collide upside or downside of game field?
			Field::CollisionType collision_RightPaddle_Field = m_Field->checkBorderCollision(*m_RightPaddle);

			if (collision_RightPaddle_Field != Field::COLLIDE_None) {
				m_RightPaddle->velocity = Vector2();

				if (collision_RightPaddle_Field == Field::COLLIDE_Top)
					m_RightPaddle->position = Vector2(m_RightPaddle->position.x, m_Field->getHeight()/2 - m_RightPaddle->getHeight()/2);
				else
					m_RightPaddle->position = Vector2(m_RightPaddle->position.x, -m_Field->getHeight()/2 + m_RightPaddle->getHeight()/2);
			}
		}
	}

	/* ==================================================
	 * ================== METHOD run() ==================
	 * ================================================== */
	void Game::run() {

		int scoreFirstPlayer = m_Match->getScore(*m_FirstPlayer);
		int scoreSecondPlayer = m_Match->getScore(*m_SecondPlayer);

		std::cout << "===== Score =====" << std::endl;
		std::cout << "P1: " << scoreFirstPlayer << "   -   " << scoreSecondPlayer << " :P2" << std::endl;

		//Main loop of Pong game.
		while (!glfwWindowShouldClose(mp_Window) && !m_Match->isEnded()) {
			float currentTime = (float) glfwGetTime();
			float deltaTime = currentTime - oldTime;

			/* ---------- Check objects collide. ---------- */
			checkCollisionObjects();

			/* ---------- Update controllers and objects. ---------- */
			m_FirstPlayer->update(deltaTime);
			m_SecondPlayer->update(deltaTime);

			m_LeftPaddle->update(deltaTime);
			m_RightPaddle->update(deltaTime);
			m_Ball->update(deltaTime);

			/* ---------- Update renderer. ---------- */
			m_Render->updatePaddle(*m_LeftPaddle);
			m_Render->updatePaddle(*m_RightPaddle);
			m_Render->updateBall(*m_Ball);
			m_Render->render();

			/* ---------- Update other stuff ---------- */
			glfwSwapBuffers(mp_Window);
			glfwPollEvents();

			oldTime = currentTime;
		}

		//Diplay player has won.
		if (m_Match->isEnded()) {
			int scoreFirstPlayer = m_Match->getScore(*m_FirstPlayer);
			int scoreSecondPlayer = m_Match->getScore(*m_SecondPlayer);

			std::cout << "Match ended: P" << (scoreFirstPlayer > scoreSecondPlayer? "1" : "2") << " has won!" << std::endl;
		}
	}
}