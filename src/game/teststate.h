#pragma once

#include "gamestate.h"
#include "Box2D/Box2D.h"

namespace Jam {

	class TestState : public GameState {
	public:

		void init();
		void update(double deta);
		void exit();

	private:

		void _initTestStuff();

		b2World* _world;

	};
}