#include "level.h"

using namespace Jam;

Level::Level(Jam::Root* root, RenderEngine* renderEngine, int difficulty)
	: _root(root), _renderEngine(renderEngine), _difficulty(difficulty)
{
	//General
	_chunksX = 5 + difficulty * 2;
	_chunksY = 5 + difficulty;

	//World
	_world = new b2World(b2Vec2(0, -9.82f));
	
	//Level background
	Entity* terrain = new Entity();
	terrain->add(new Terrain(this));

	_root->addNode(0, "terrain", (Node*) terrain);

	//Level shop
	Entity* shop = new Entity();
	shop->add(new Shop(this, (1 + difficulty) * 5));

	_root->addNode(0, "shop", (Node*) shop);

	//Traps


	//Playing music
	AudioHandler::preload("dunes", "audio/dunes.wav");
	while (!AudioHandler::ready());

	_music = new Sound();

	_music->setGain(0.1f);
	_music->setLooping(true);
	_music->play("dunes");


	//Camera setup
	_renderEngine->getCamera()->transform.setPosition(1.5f * Terrain::CHUNK_SIZE, -1.5f * Terrain::CHUNK_SIZE);
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

	//_world->Step(delta, 8, 2);
}

void Level::buyChunk(unsigned int x, unsigned int y)
{
	((Entity*)_root->getNode("terrain"))->get<Terrain>()->buyChunk(x, y);
}

void Level::sellChunk(unsigned int x, unsigned int y)
{
	((Entity*)_root->getNode("terrain"))->get<Terrain>()->sellChunk(x, y);
}

void Level::complete()
{
	Jam::GameStateLibrary::getGameState("play")->getCurrentRoot()->deleteNode("level");
}

glm::vec2 Level::toGLSpace(RenderEngine* renderEngine, glm::vec2 windowCoords)
{
	int w, h;
	renderEngine->getWindow().getSize(&w, &h);

	//X
	/* Jag kunde inte motst�
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

glm::vec2 Level::toChunkCords(Jam::RenderEngine * renderEngine, glm::vec2 windowCoords) {
	return glm::vec2();
}

Level::~Level()
{
	_music->stop();
	delete _world;
	_world = nullptr;
}

void Level::buyTrap(Item item, unsigned int x, unsigned int y)
{
	Trap trap;
	trap.trapType = TrapType(item - 1);
	trap.x = x;
	trap.y = y;
	
	Entity* entity = new Entity();

	Material material;

	switch (trap.trapType) {
	case TRAP_TYPE_SPIKE:
		material.spriteSheet = true;
		material.texture = "spike_trap";
		material.ssOffsetX = 0;
		material.ssOffsetY = 0;

		entity->transform.setPosition(x + .5f, -(int)y - .5f);
		entity->add(new SpikeTrap(_renderEngine, _world, material));
		break;
	case TRAP_TYPE_ARROW:
		material.texture = "arrow_trap";

		entity->transform.setPosition(x + .5f, -(int)y);
		entity->add(new ArrowTrap(_renderEngine, _world, material));
		break;
	}

	trap.name = "trap_" + std::to_string(x) + "_" + std::to_string(y);
	_root->addNode(0, trap.name, (Node*)entity);
	entity->_rootEnter();

	_traps.push_back(trap);
}

void Level::sellTrap(Item item, unsigned int x, unsigned int y)
{
	for (int i = 0; i < _traps.size(); i++) {
		if (_traps[i].trapType == TrapType(item - 1) && _traps[i].x == x && _traps[i].y == y) {
			((Entity*)_root->getNode(_traps[i].name))->_rootExit();
			_root->deleteNode(_traps[i].name);
			_traps.erase(_traps.begin() + i);
			break;
		}
	}
}

Trap Level::getTrap(unsigned int x, unsigned int y)
{
	for (Trap t : _traps) {
		if (t.x == x && t.y == y)
			return t;
	}

	Trap t;
	t.x = -1;
	return t;
}

Tile Level::getTile(unsigned int x, unsigned int y)
{
	return ((Entity*)_root->getNode("terrain"))->get<Terrain>()->getTile(x, y);
}