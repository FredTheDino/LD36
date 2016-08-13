#pragma once

#include "pie.h"

namespace Jam
{
	//Forward declarations
	class Pie;

	class GameStateManager
	{
	public:
		GameStateManager(Pie& pie);
		~GameStateManager();

		void update();

	private:

		Pie& _pie;

	};
}