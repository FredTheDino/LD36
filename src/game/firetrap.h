#include "trapcomponent.h"

namespace Jam {

	class FireTrap : public TrapComponent{
	public:
		FireTrap(RenderEngine* engine, b2World* world, Root* root);
		~FireTrap();

		virtual void _init();

		virtual void _update(double delta);

		virtual void _end();

		virtual void _fire();

		virtual void _reset();

	private:
		b2World* _world;
		Root* _root;
		Entity* _flame;
	};
}