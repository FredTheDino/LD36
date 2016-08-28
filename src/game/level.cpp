#include "level.h"

using namespace Jam;

Level::Level(Jam::Root* root, RenderEngine* renderEngine, int difficulty)
	: _root(root), _renderEngine(renderEngine), _difficulty(difficulty)
{
	//General
	_chunksX = 5 + difficulty * 2 - 1;
	_chunksY = 5 + difficulty - 1;

	//Level background
	Entity* levelBackground = new Entity();
	levelBackground->add(new LevelBackground(this));

	_root->addNode(0, "level_background", (Node*) levelBackground);
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