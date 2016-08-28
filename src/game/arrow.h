#pragma once
#include "component.h"
#include "renderengine.h"
#include "Box2D/Box2D.h"

namespace Jam {
	class Arrow: public Component {
	public:
		//direction should be passed in as radians
		Arrow(RenderEngine* engine, b2World* world, Material material, float direction);
		~Arrow();
		
		virtual void _init();

		virtual void _update(double delta);

		virtual void _end();

	private:
		float _speed = 50;
		float _direction;

		b2World* _world;
		RenderEngine* _engine;
		Material _material;
	};
}