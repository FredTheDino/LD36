#pragma once

#include "Box2D/Box2D.h"
#include "box2dcomponent.h"

namespace Jam {
	class Box2DListener: public b2ContactListener {
		friend Box2DComponent;

	public:
		void BeginContact(b2Contact* contact);

		void EndContact(b2Contact* contact);
	};
}