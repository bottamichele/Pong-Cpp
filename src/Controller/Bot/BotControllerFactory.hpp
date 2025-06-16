/* =======================================================
 * BotControllerFactory.hpp: Builder of a bot controller.
 * ======================================================= */
#pragma once

#include <memory>

#include "Controller/Controller.hpp"

#include "BasicBotController.hpp"

#include "Game/Objects/Field.hpp"
#include "Game/Objects/Ball.hpp"
#include "Game/Objects/Paddle.hpp"

namespace Pong {
	/// <summary>
	/// Type of bot controller that want to be used.
	/// </summary>
	enum BotControllerType {
		BOT_Basic,				//A basic bot controller.
	};

	/// <summary>
	/// An set of data may be useful to contructor of a bot controller.
	/// </summary>
	struct BotControllerFactoryInformation {
		std::shared_ptr<Field> field;					//Game field.
		std::shared_ptr<Paddle> leftPaddle;				//Paddle at left-side of field.
		std::shared_ptr<Paddle> rightPaddle;			//Paddle at right-side of field.
		std::shared_ptr<Ball> ball;						//Ball.
		PlayerPosition positionPlayer;					//Position of player.
	};

	/// <summary>
	/// A bot controller builder.
	/// </summary>
	class BotControllerFactory {
		public:
			/// <summary>
			/// Create a bot controller.
			/// </summary>
			/// <param name="data">Data can be used by constructor of a bot controller.</param>
			/// <param name="botCtrlType">Type of bot controller to use.</param>
			/// <returns></returns>
			static std::shared_ptr<Controller> create(BotControllerFactoryInformation& data, BotControllerType botCtrlType=BOT_Basic) {
				if (botCtrlType == BOT_Basic) {
					return std::make_shared<BasicBotController>(data.positionPlayer,
																data.positionPlayer == POSITION_Left ? data.leftPaddle : data.rightPaddle,
																data.ball);
				}
				//else if (botCtrlType == BOT_BasicQLearning) {
				//	return std::make_shared<BasicQLearningBotController>(data.positionPlayer,
				//														data.positionPlayer==POSITION_Left? data.leftPaddle : data.rightPaddle,
				//														data.ball);
				//}
			}
	};
}