#pragma once

#include "root.h"

#include "terrain.h"

#include "shop.h"

#include "renderengine.h"

#include "sound.h"

#include "Box2D/Box2D.h"

#include "guifader.h"

#include "spiketrap.h"
#include "arrowtrap.h"

class Terrain;
class Shop;

struct Tile;

enum TrapType {
	TRAP_TYPE_SPIKE,
	TRAP_TYPE_ARROW,
	TRAP_TYPE_FIRE
};


struct Trap {
	TrapType trapType;
	int x;
	int y;
	std::string name;
};

class Level
{
public:
	Level(Jam::Root* root, Jam::RenderEngine* renderEngine, int difficulty);
	~Level();

	void update(double delta);
	
	void buyChunk(unsigned int x, unsigned int y);
	void sellChunk(unsigned int x, unsigned int y);

	void buyTrap(Item item, unsigned int x, unsigned int y);
	void sellTrap(Item item, unsigned int x, unsigned int y);

	void complete();

	Trap getTrap(unsigned int x, unsigned int y);

	Tile getTile(unsigned int x, unsigned int y);

	static glm::vec2 toGLSpace(Jam::RenderEngine* renderEngine, glm::vec2 windowCoords);

private:

	Jam::Root* _root;

	b2World* _world;

	std::vector<Trap> _traps;

	Jam::Sound* _music;

	Jam::RenderEngine* _renderEngine;

	int _difficulty;

	int _chunksX;
	int _chunksY;

	friend Terrain;
	friend Shop;
};