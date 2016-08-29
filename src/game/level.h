#pragma once

#include "root.h"

#include "terrain.h"

#include "shop.h"

#include "renderengine.h"

#include "sound.h"

#include "Box2D/Box2D.h"

#include "guifader.h"

class Terrain;
class Shop;

class Level
{
public:
	Level(Jam::Root* root, Jam::RenderEngine* renderEngine, int difficulty);
	~Level();

	void update(double delta);
	
	void buyChunk(unsigned int x, unsigned int y);
	void sellChunk(unsigned int x, unsigned int y);

	void complete();

	static glm::vec2 toGLSpace(Jam::RenderEngine* renderEngine, glm::vec2 windowCoords);

	int getChunksX() { return _chunksX; }
	int getChunksY() { return _chunksY; }

private:

	Jam::Root* _root;
	
	b2World* _world;

	Jam::Sound* _music;

	Jam::RenderEngine* _renderEngine;

	int _difficulty;

	int _chunksX;
	int _chunksY;

	friend Terrain;
	friend Shop;
};