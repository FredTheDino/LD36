#include "trapcomponent.h"

namespace Jam {

	class FireTrap {
	public:
		FireTrap();
		~FireTrap();

		virtual void _init();

		virtual void _update();

		virtual void _end();

		virtual void _fire();

		virtual void _reset();

	private:
		b2World* _world;
		RenderEngine* _engine;
	};
}