#include "trapcomponent.h"

namespace Jam {
	class SpikeTrap: public TrapComponent {
	public:
		SpikeTrap(RenderEngine* engine, b2World* world, Material material);
		~SpikeTrap();

		virtual void _init();

		virtual void _update(double delta);

		virtual void _fire();

		virtual void _reset();

	private:
		b2World* _world = nullptr;
	};
}