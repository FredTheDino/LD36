#pragma once
#include "component.h"
#include "renderengine.h"

namespace Jam {

	enum class Death {
		FIRE,
		PHYSICAL,
	};

	class Adventurer : public Component {

	public:
		Adventurer(RenderEngine* engine, b2World* world);
		~Adventurer();

		virtual void _init();

		virtual void _update(double delta);

		virtual void _end();

		bool isAlive() { return _alive; }

		void die(Death death);

	private:
		b2World* _world = nullptr;
		RenderEngine* _engine = nullptr;

		bool _alive = false;

	};
}