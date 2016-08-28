#pragma once

#include "trapcomponent.h"

namespace Jam {

	class ArrowTrap : public TrapComponent {
	public:
		ArrowTrap(RenderEngine* engine, b2World* world, Material material);
		~ArrowTrap();

		virtual void _init();

		virtual void _update(double delta);

		virtual void _end();

		virtual void _fire();

		virtual void _reset();

	private:

		b2World* _world = nullptr;

	};
}