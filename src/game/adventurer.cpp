#include "adventurer.h"
#include "Box2D/Box2D.h"
#include "box2dcomponent.h"
#include "level.h"
#include "entity.h"

#include <random>

Jam::Adventurer::Adventurer(RenderEngine * engine, b2World * world, Level* level) {
	_engine = engine;
	_world = world;
	_level = level;
	_lastChunk = glm::vec2(1, 1);
}

Jam::Adventurer::~Adventurer() {}

int getDirectionFromVector(glm::vec2 vec) {
	return -(vec.y - 1) + vec.x - abs(vec.x);
}

void Jam::Adventurer::_init() {
	getParent()->scale(1);

	Material material;
	material.texture = "default";
	material.baseColor = glm::vec4(1.0, 0.0, 1.0, 1.0);

	getParent()->add(new Renderer(_engine, 200, "quad", material));
	_rootEnter();
	getParent()->add(new Box2DComponent(_world, BodyType::DYNAMICBODY, false, 0.5, 0.5, 0.5));

	getParent()->get<Box2DComponent>()->body->SetGravityScale(0);

	for (size_t x = 0; x < _level->getChunksX(); x++) {
		_map.push_back(std::vector<MapNotation>());
		_map[x].resize(_level->getChunksY());
	}
	_terrain = ((Entity*)((Root*) GameStateLibrary::getGameState("play")->getRoot("game")->getNode("level"))->getNode("terrain"))->get<Terrain>();
}

void Jam::Adventurer::_update(double delta) {
	static float centerX = 1.5;
	static float centerY = -2.5;
	static float errorMargin = 0.03;

	getParent()->get<Box2DComponent>()->body->ApplyForceToCenter(b2Vec2(25.0 * delta, 0.0), true);

	if (_updateDirection) {

		float x = getParent()->getPosition().x - _lastChunk.x * Terrain::CHUNK_SIZE;
		float y = getParent()->getPosition().y + _lastChunk.y * Terrain::CHUNK_SIZE;

		if (x < centerX + errorMargin && y < centerY + errorMargin &&
			x > centerX - errorMargin && y > centerY - errorMargin) {
			
			_updateDirection = false;
			getParent()->setPosition(glm::vec3(
				centerX + _lastChunk.x * Terrain::CHUNK_SIZE, 
				centerY - _lastChunk.y * Terrain::CHUNK_SIZE,
				0
				));

			bool foundDirection = false;
			int direction = rand() % 4;

			printf("Searching for direction!\n");

			MapNotation notation = _map[_lastChunk.x][_lastChunk.y];

			for (size_t i = 0; i < 4; i++) {
				if (notation[direction] == UNVISITED) {
					printf("Found unvisited direction: %i\n", direction);
					foundDirection = true;
					break;
				}
				direction++;
			}

			if (!foundDirection) {
				for (size_t i = 0; i < 4; i++) {
					if (notation[direction] == VISITED) {
						printf("Found visited direction: %i\n", direction);
						foundDirection = true;
						break;
					}
					direction++;
				}
			}
			if (!foundDirection) {
				for (size_t i = 0; i < 4; i++) {
					if (notation[direction] == COMPLEATED) {
						printf("Found compleated direction: %i\n", direction);
						foundDirection = true;
						break;
					}
					direction++;
				}
			}

			switch (direction % 4) {
				case 0:
					_direction.x = 0;
					_direction.y = 1;
					break;
				case 1:
					_direction.x = 1;
					_direction.y = 0;
					break;
				case 2:
					_direction.x = 0;
					_direction.y = -1;
					break;
				case 3:
					_direction.x = -1;
					_direction.y = 0;
					break;
			}

		}
	}
	
	
	//Get our current posiiton
	glm::vec2 currentChunk;
	//Convert it to a chunk coordinate
	currentChunk.x = floor(getParent()->getPosition().x / (float)Terrain::CHUNK_SIZE);
	currentChunk.y = floor(-(getParent()->getPosition().y / (float)Terrain::CHUNK_SIZE));

	//Check if we moved
	if (currentChunk != _lastChunk || _firstFrame) {
	
		_map[0][0][0] = UNVISITED;
		
		if (_map[0][0][0] == UNVISITED) {
			printf("Setting works! :D\n");
		} else {
			printf("Oh dear...\n");
		}

		printf("ChunkX: %f\t ChunkY: %f\n", currentChunk.x, currentChunk.y);
		if (!_firstFrame) {
			//Check if the map should be updated
			Direction acceptability = Direction::UNAVAILABLE;

			int target = getDirectionFromVector(_lastChunk - currentChunk);

			acceptability = _map[currentChunk.x][currentChunk.y].getLowestPriority(target);

			printf("Acceptability: %i\tDirection: %i\n", acceptability, target);


			if (acceptability == UNVISITED) acceptability = VISITED;
			//Make sure the returnpath isn't flagged as UNAVAILABLE
			if (acceptability == UNAVAILABLE) acceptability = COMPLEATED;
			_map[currentChunk.x][currentChunk.y].set(target, acceptability);

			//Make sure you can't walk in circles
			_map[_lastChunk.x][_lastChunk.y].set(target + 2, acceptability == VISITED ? COMPLEATED : acceptability);
		}

		_firstFrame = false;
		_updateDirection = true;
		MapNotation* notation = &_map[currentChunk.x][currentChunk.y];

		//If it fails, make sure the adventurer doesn't go there
		try {
			//Check if there is an exit to the south, and update the map
			if (_terrain->getChunk(currentChunk.x, currentChunk.y - 1).type == CHUNK_TYPE_SOLID) {
				(*notation).north = Direction::UNAVAILABLE;
			} else {
				/*if (_terrain->getChunk(currentChunk.x, currentChunk.y - 1).tiles[1].type == TILE_TYPE_LADDER) {
					(*notation)[0] = _map[currentChunk.x][currentChunk.y - 1].getLowestPriority();
				} else {//*/
				(*notation).north = _map[currentChunk.x][currentChunk.y - 1].getLowestPriority();
				//}
			}
		} catch (std::out_of_range outOfRange) {
			_map[currentChunk.x][currentChunk.y].north = Direction::UNAVAILABLE;
		}

		try {
			//Check if there is an exit to the north, and update the map
			if (_terrain->getChunk(currentChunk.x, currentChunk.y + 1).type == CHUNK_TYPE_SOLID) {
				(*notation).south = Direction::UNAVAILABLE;
			} else {
				(*notation).south = _map[currentChunk.x][currentChunk.y + 1].getLowestPriority();
			}
		} catch (std::out_of_range outOfRange) {
			/*if (_terrain->getChunk(currenChunk.x, currentChunk.y + 1).tiles[1].type == TILE_TYPE_LADDER) {
				(*notation)[0] = _map[currentChunk.x][currentChunk.y - 1].getLowestPriority();
			} else {
			*/	(*notation).south = Direction::UNAVAILABLE;
			//}
		}

		try {
			//Check if there is an exit to the east, and update the map
			if (_terrain->getChunk(currentChunk.x + 1, currentChunk.y).type == CHUNK_TYPE_SOLID) {
				(*notation).east = Direction::UNAVAILABLE;
			} else {
				(*notation).east = _map[currentChunk.x + 1][currentChunk.y].getLowestPriority();
			}
		} catch (std::out_of_range outOfRange) {
			(*notation).east = Direction::UNAVAILABLE;
		}

		try {
			//Check if there is an exit to the west, and update the map
			if (_terrain->getChunk(currentChunk.x - 1, currentChunk.y).type == CHUNK_TYPE_SOLID) {
				(*notation).west = Direction::UNAVAILABLE;
			} else {
				(*notation).west = _map[currentChunk.x - 1][currentChunk.y].getLowestPriority();
			}
		} catch (std::out_of_range outOfRange) {
			(*notation).west = Direction::UNAVAILABLE;
		}

		//Update the current chunk
		_lastChunk = currentChunk;

		printf("Mapstatus:\nNorth: %i\tEast: %i\nSouth: %i\tWest: %i\n\n",
			   (*notation)[0], (*notation)[1], (*notation)[2], (*notation)[3]);

		printf("================================================================");

		/*


		printf("===============================MAP===============================\n\n");

		for (size_t x = 0; x < _map.size(); x++) {
			for (size_t y = 0; y < _map[x].size(); y++) {
				MapNotation n = _map[x][y];
				printf("\tN: %i, E: %i, S: %i, W: %i", n[0], n[1], n[2], n[3]);
			}
			printf("\n");
		}
*/
	}
	b2Vec2 f = b2Vec2(_direction.x * _speed, _direction.y * _speed);

	getParent()->get<Box2DComponent>()->body->SetLinearVelocity(f);
}

void Jam::Adventurer::_end() {}

void Jam::Adventurer::die(Death death) {
	printf("An adventurer died");
}
