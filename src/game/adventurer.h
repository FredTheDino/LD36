#pragma once
#include "component.h"
#include "renderengine.h"
#include "level.h"
#include "terrain.h"

namespace Jam {

	enum Direction {
		COMPLEATED,
		VISITED,
		UNVISITED,
		UNAVAILABLE,
	};

	struct MapNotation {
		Direction north = Direction::UNVISITED;
		Direction east = Direction::UNVISITED;
		Direction south = Direction::UNVISITED;
		Direction west = Direction::UNVISITED;

		Direction& operator[] (int i) {
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

		Direction operator[] (int i) const {
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

		Direction getLowestPriority(int exclude = -1) {
			
			Direction lowest = Direction::UNAVAILABLE;
			for (size_t i = 0; i < 4; i++) {
				if (i == exclude) continue;
				lowest = lowest <= (*this)[i] ? lowest : (*this)[i];
			}
			return lowest;
		}

	};

	enum class Death {
		FIRE,
		PHYSICAL,
	};

	class Adventurer : public Component {

	public:
		Adventurer(RenderEngine* engine, b2World* world, Level* level);
		~Adventurer();

		virtual void _init();

		virtual void _update(double delta);

		virtual void _end();

		bool isAlive() { return _alive; }

		void die(Death death);

	private:
		b2World* _world = nullptr;
		RenderEngine* _engine = nullptr;
		Level* _level;
		Terrain* _terrain = nullptr;

		float _speed = 2;

		glm::vec2 _direction;
		glm::vec2 _lastChunk = glm::vec2(-1, -1);

		std::vector<std::vector<MapNotation>> _map;

		bool _updateDirection = false;
		bool _firstFrame = true;
		bool _alive = true;

	};
}