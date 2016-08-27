#pragma once
#include "component.h"

namespace Jam {

	enum class Death {
		FIRE,
		PHYSICAL,
	};

	class Adventurer : public Component {

	public:
		Adventurer() {};
		~Adventurer() {};

		bool isAlive() { return _alive; }

		void die(Death death) {};

	private:

		bool _alive = false;

	};
}