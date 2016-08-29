#include "adventurer.h"
#include "Box2D/Box2D.h"
#include "box2dcomponent.h"
#include "level.h"

Jam::Adventurer::Adventurer(RenderEngine * engine, b2World * world, Level* level) {
	_engine = engine;
	_world = world;
	_level = level;
	_lastChunk = glm::vec2(1, 1);
}

Jam::Adventurer::~Adventurer() {}

int getIdFromVector(glm::vec2 vec) {
	return -(vec.y - 1) + vec.x - abs(vec.x);
}

void Jam::Adventurer::_init() {
	getParent()->scale(1);
	getParent()->add(new Renderer(_engine, 5, "quad", "default"));
	getParent()->add(new Box2DComponent(_world, BodyType::DYNAMICBODY, false, 0.5, 0.5, 0.5, 0.0, 0.0));

	for (size_t x = 0; x < _level->getChunksX(); x++) {
		_map.push_back(std::vector<MapNotation>());
		for (size_t y = 0; y < _level->getChunksY(); y++) {
			_map[x].push_back(MapNotation());
		}
	}

	_terrain = ((Entity*) GameStateLibrary::getGameState("play")->getRoot("terrain"))->get<Terrain>();
}

void Jam::Adventurer::_update(double delta) {
	getParent()->get<Box2DComponent>()->body->ApplyForceToCenter(b2Vec2(25.0 * delta, 0.0), true);

	//Get our current posiiton
	glm::vec2 currentChunk;
	//Convert it to a chunk coordinate
	currentChunk.x = floor(getParent()->getPosition().x / Terrain::CHUNK_SIZE);
	currentChunk.y = floor(getParent()->getPosition().y / Terrain::CHUNK_SIZE);
	//Check if we moved
	if (currentChunk != _lastChunk) {

		//AI Stuff
		Direction acceptability = Direction::UNAVAILABLE;

		int target = getIdFromVector(currentChunk - _lastChunk);

		for (size_t i = 0; i < 4; i++) {
			acceptability = _map[_lastChunk.x][_lastChunk.y][target] < acceptability? _map[_lastChunk.x][_lastChunk.y][target] : acceptability;
		}
		_map[_lastChunk.x][_lastChunk.y][target] == acceptability;

		//Get the tile
		_lastChunk = currentChunk;
		Chunk c = _terrain->getChunk(_lastChunk.x, _lastChunk.y);

		short x, y;

		for (size_t i = 0; i < c.tiles.size(); i++) {
			y = floor(i / Terrain::CHUNK_SIZE) ;
			x = i % Terrain::CHUNK_SIZE - y * Terrain::CHUNK_SIZE;

			if (y == 0) {
				//Check if tile type == 
				/*
				_map[x][y][0]
				*/
			}
		}
	}
}

void Jam::Adventurer::_end() {}

void Jam::Adventurer::die(Death death) {
	printf("An adventurer died");
}
