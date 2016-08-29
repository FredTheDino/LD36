#pragma once
#include "component.h"
#include "renderengine.h"

namespace Jam {

	enum Direction {
		COMPLEATED,
		VISITED,
		UNVISITED
	};

	struct MapNotation {
		Direction north = Direction::UNVISITED;
		Direction east = Direction::UNVISITED;
		Direction south = Direction::UNVISITED;
		Direction west = Direction::UNVISITED;

		int operator[] (int i) {
			i %= 4;
			switch (i) {
				case 0:
					return north;
				case 1:
					return east;
				case 2:
					return south;
				case 3:
					return west;
				default:
					return north;
			}
		}
	};

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

		glm::vec2 _direction;

		std::vector<std::vector<MapNotation>> _map;

		bool _alive = false;

	};
}