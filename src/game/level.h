#pragma once

#include "root.h"

#include "levelbackground.h"

#include "shop.h"

#include "renderengine.h"

#include "sound.h"

class LevelBackground;
class Shop;

class Level
{
public:
	Level(Jam::Root* root, Jam::RenderEngine* renderEngine, int difficulty);

	void update(double delta);
	
	void buyChunk(unsigned int x, unsigned int y);
	void sellChunk(unsigned int x, unsigned int y);

	static glm::vec2 toGLSpace(Jam::RenderEngine* renderEngine, glm::vec2 windowCoords);

private:

	Jam::Root* _root;

	Jam::Sound* _music;

	Jam::RenderEngine* _renderEngine;

	int _difficulty;

	int _chunksX;
	int _chunksY;

	friend LevelBackground;
	friend Shop;
};