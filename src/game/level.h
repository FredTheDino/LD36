#pragma once

#include "root.h"

#include "levelbackground.h"

#include "renderengine.h"

class LevelBackground;

class Level
{
public:
	Level(Jam::Root* root, Jam::RenderEngine* renderEngine, int difficulty);

	void update(double delta);
	
	static glm::vec2 toGLSpace(Jam::RenderEngine* renderEngine, glm::vec2 windowCoords);

private:
	
	Jam::Root* _root;

	Jam::RenderEngine* _renderEngine;

	int _difficulty;

	int _chunksX;
	int _chunksY;

	friend LevelBackground;
};