#include "level.h"

using namespace Jam;

Level::Level(Jam::Root* root, RenderEngine* renderEngine, int difficulty)
	: _root(root), _renderEngine(renderEngine), _difficulty(difficulty)
{
	//General
	_chunksX = 5 + difficulty * 2;
	_chunksY = 5 + difficulty;

	//Level background
	Entity* terrain = new Entity();
	terrain->add(new LevelBackground(this));

	_root->addNode(0, "terrain", (Node*) terrain);

	//Level shop
	Entity* shop = new Entity();
	shop->add(new Shop(this));

	_root->addNode(0, "shop", (Node*) shop);

	//Playing music
	AudioHandler::preload("dunes", "audio/dunes.wav");
	while (!AudioHandler::ready());

	_music = new Sound();

	_music->setGain(0.1f);
	_music->setLooping(true);
	_music->play("dunes");

	//Camera setup
	_renderEngine->getCamera()->transform.setPosition(1.5f * LevelBackground::CHUNK_SIZE, -1.5f * LevelBackground::CHUNK_SIZE);
	_renderEngine->getCamera()->transform.setScale(5.0f);
}


void Level::update(double delta)
{
	if (InputHandler::keyDown("arrow_up"))
		_renderEngine->getCamera()->transform.translateY(delta * 4);
	if (InputHandler::keyDown("arrow_down"))
		_renderEngine->getCamera()->transform.translateY(-delta * 4);
	if (InputHandler::keyDown("arrow_left"))
		_renderEngine->getCamera()->transform.translateX(-delta * 4);
	if (InputHandler::keyDown("arrow_right"))
		_renderEngine->getCamera()->transform.translateX(delta * 4);

	if (InputHandler::keyDown("zoom_in"))
		_renderEngine->getCamera()->transform.addScale(-delta * 4);
	if (InputHandler::keyDown("zoom_out"))
		_renderEngine->getCamera()->transform.addScale(delta * 4);
}

void Level::buyChunk(unsigned int x, unsigned int y)
{
	((Entity*)_root->getNode("terrain"))->get<LevelBackground>()->buyChunk(x, y);
}

void Level::sellChunk(unsigned int x, unsigned int y)
{
	((Entity*)_root->getNode("terrain"))->get<LevelBackground>()->sellChunk(x, y);
}

glm::vec2 Level::toGLSpace(RenderEngine* renderEngine, glm::vec2 windowCoords)
{
	int w, h;
	renderEngine->getWindow().getSize(&w, &h);

	//X
	/* Jag kunde inte motstå
	windowCoords.x /= w;
	windowCoords.x *= ((float)w) / h * 2;
	windowCoords.x -= ((float)w) / h;
	*/
	windowCoords.x = windowCoords.x / h * 2 - ((float) w) / h;
	windowCoords.x *= renderEngine->getCamera()->getTransform().scale.x;

	windowCoords.x += renderEngine->getCamera()->getTransform().position.x;

	//Y
	windowCoords.y /= -h;
	windowCoords.y *= 2;
	windowCoords.y += 1;
	windowCoords.y *= renderEngine->getCamera()->getTransform().scale.y;

	windowCoords.y += renderEngine->getCamera()->getTransform().position.y;

	return windowCoords;
}