#include "terrain.h"

using namespace Jam;

const unsigned int Terrain::CHUNK_SIZE = 3;

Terrain::Terrain(Level* level)
	: _level(level)
{
	
}

void Terrain::_init()
{
	_generateChunks();
	_generateMesh();
}

void Terrain::_update(double delta)
{
	
}

void Terrain::buyChunk(unsigned int x, unsigned int y)
{
	Chunk& c = _getChunk(x, y);

	if (c.type == CHUNK_TYPE_NORMAL) {
		sellChunk(x, y);
		return;
	}

	if (c.type != CHUNK_TYPE_SOLID)
		return;

	for (unsigned int i = 0; i < c.tiles.size(); i++) {
		switch (c.tiles[i].terrainOffset) {
		case 0: c.tiles[i].terrainOffset = 12; break;
		case 3: c.tiles[i].terrainOffset = 15; break;
		case 5: c.tiles[i].terrainOffset = 14; break;
		case 7: c.tiles[i].terrainOffset = 13; break;
		}

		c.tiles[i].tileType = TILE_TYPE_NORMAL;
		
		if(floor(i / CHUNK_SIZE) == CHUNK_SIZE - 1) {

			if ((getChunk(x - 1, y).type != CHUNK_TYPE_SOLID && i % CHUNK_SIZE == 0)) {
				_getTile(c.tiles[i].x - 1, c.tiles[i].y).tileType = TILE_TYPE_EXIT;
				c.tiles[i].tileType = TILE_TYPE_EXIT;
			}

			if ((getChunk(x + 1, y).type != CHUNK_TYPE_SOLID && i % CHUNK_SIZE == CHUNK_SIZE - 1)) {
				_getTile(c.tiles[i].x + 1, c.tiles[i].y).tileType = TILE_TYPE_EXIT;
				c.tiles[i].tileType = TILE_TYPE_EXIT;
			}

		}
	}

	c.type = CHUNK_TYPE_NORMAL;

	_updateLadders(x, y, true);

	_level->_world->DestroyBody(c.body);

	updateChunk(x, y);
}

void Terrain::_updateLadders(unsigned int x, unsigned int y, bool chain)
{
	if (_getChunk(x, y).type != CHUNK_TYPE_NORMAL)
		return;

	int start = 0;

	if (chain) {
		_updateLadders(x - 1, y);
		_updateLadders(x + 1, y);
	}

	//Find bottom of pit
	for (int i = y; i < _level->_chunksY; i++) {
		if (_getChunk(x, i + 1).type == CHUNK_TYPE_SOLID) {
			start = i;
			break;
		}
	}

	int hits = 0; //How many branches were descovered?
	int first = 0; //At what Y coordinate was the first branch?
	int last = 0; //At what Y coordinate was the last branch?

	//Check if ladders should be placed
	for (int i = start; i > 0; i--) {
		if (_getChunk(x, i).type == CHUNK_TYPE_NORMAL) {
			if ((_getChunk(x - 1, i).type != CHUNK_TYPE_SOLID && _getChunk(x - 1, i + 1).type == CHUNK_TYPE_SOLID) ||
					(_getChunk(x + 1, i).type != CHUNK_TYPE_SOLID && _getChunk(x + 1, i + 1).type == CHUNK_TYPE_SOLID)) {
				hits++;
				if (first == 0)
					first = i;
				last = i;
			}
		}
		else {
			break;
		}
	}

	if (hits < 2)
		return;

	//Place ladders
	for (int i = first; i > last; i--) {
		_getChunk(x, i).tiles[1].terrainOffset = 25;
		_getChunk(x, i).tiles[1].tileType = TILE_TYPE_LADDER;
		_getChunk(x, i).tiles[4].terrainOffset = 25;
		_getChunk(x, i).tiles[4].tileType = TILE_TYPE_LADDER;
		_getChunk(x, i).tiles[7].terrainOffset = 25;
		_getChunk(x, i).tiles[7].tileType = TILE_TYPE_LADDER;

		if (_getChunk(x - 1, i - 1).type != CHUNK_TYPE_SOLID && _getChunk(x - 1, i).type == CHUNK_TYPE_SOLID) {

			_getChunk(x, i).tiles[0].terrainOffset = 0;
		}

		if (_getChunk(x + 1, i - 1).type != CHUNK_TYPE_SOLID && _getChunk(x + 1, i).type == CHUNK_TYPE_SOLID) {

			_getChunk(x, i).tiles[2].terrainOffset = 0;
		}

		updateChunk(x, i);
	}

	/*
	
	if (_getChunk(x - 1, i).type != CHUNK_TYPE_SOLID) {
	if (first == 0)
	first = i;

	distance = i - first;

	_getChunk(x, i + 1).tiles[0].terrainOffset = 0;

	updateChunk(x, i + 1);
	}

	if (_getChunk(x + 1, i).type != CHUNK_TYPE_SOLID) {
	if (first == 0)
	first = i;

	distance = i - first;

	_getChunk(x, i + 1).tiles[2].terrainOffset = 0;

	updateChunk(x, i + 1);
	}
	
	*/

	/*
	for (int i = y; i > d; i--) {
		if (_getChunk(x, i).type == CHUNK_TYPE_NORMAL) {
			_getChunk(x, i).tiles[1].tileType = TILE_TYPE_LADDER;
			_getChunk(x, i).tiles[1].terrainOffset = 25;
			_getChunk(x, i).tiles[4].tileType = TILE_TYPE_LADDER;
			_getChunk(x, i).tiles[4].terrainOffset = 25;
			_getChunk(x, i).tiles[7].tileType = TILE_TYPE_LADDER;
			_getChunk(x, i).tiles[7].terrainOffset = 25;

			updateChunk(x, i);
		}
		else {
			break;
		}
	}
	*/
	/*if (_getChunk(x, y + 1).type != CHUNK_TYPE_SOLID) {
		int d = 0;

		if (_getChunk(x - 1, y).type == CHUNK_TYPE_SOLID && _getChunk(x + 1, y).type == CHUNK_TYPE_SOLID)
			return;

		for (int i = y; i < _level->_chunksY; i++) {
			if (_getChunk(x, i).type == CHUNK_TYPE_NORMAL) {
				if (_getChunk(x - 1, i).type == CHUNK_TYPE_NORMAL) {
					d = i;

					_getChunk(x, i + 1).tiles[0].terrainOffset = 0;

					updateChunk(x, i + 1);
				}

				if (_getChunk(x + 1, i).type == CHUNK_TYPE_NORMAL) {
					d = i;

					_getChunk(x, i + 1).tiles[2].terrainOffset = 0;

					updateChunk(x, i + 1);
				}
			}
			else {
				break;
			}
		}

		for (int i = y; i <= d; i++) {
			if (d == 0)
				break;
			if (_getChunk(x, i).type == CHUNK_TYPE_NORMAL) {
				_getChunk(x, i).tiles[1].tileType = TILE_TYPE_LADDER;
				_getChunk(x, i).tiles[1].terrainOffset = 25;
				_getChunk(x, i).tiles[4].tileType = TILE_TYPE_LADDER;
				_getChunk(x, i).tiles[4].terrainOffset = 25;
				_getChunk(x, i).tiles[7].tileType = TILE_TYPE_LADDER;
				_getChunk(x, i).tiles[7].terrainOffset = 25;

				updateChunk(x, i);
			}
			else {
				break;
			}
		}
	}*/
}

void Terrain::sellChunk(unsigned int x, unsigned int y)
{
	Chunk& c = _getChunk(x, y);

	if (c.type == CHUNK_TYPE_SOLID) {
		buyChunk(x, y);
		return;
	}

	if (c.type != CHUNK_TYPE_NORMAL)
		return;

	for (unsigned int i = 0; i < c.tiles.size(); i++) {
		switch (c.tiles[i].terrainOffset) {
		case 12: c.tiles[i].terrainOffset = 0; break;
		case 15: c.tiles[i].terrainOffset = 3; break;
		case 14: c.tiles[i].terrainOffset = 5; break;
		case 13: c.tiles[i].terrainOffset = 7; break;
		}

		c.tiles[i].tileType = TILE_TYPE_SOLID;

		if (floor(i / CHUNK_SIZE) == CHUNK_SIZE - 1) {

			if ((getChunk(x - 1, y).type != CHUNK_TYPE_SOLID && i % CHUNK_SIZE == 0)) {
				_getTile(c.tiles[i].x - 1, c.tiles[i].y).tileType = TILE_TYPE_NORMAL;
			}

			if ((getChunk(x + 1, y).type != CHUNK_TYPE_SOLID && i % CHUNK_SIZE == CHUNK_SIZE - 1)) {
				_getTile(c.tiles[i].x + 1, c.tiles[i].y).tileType = TILE_TYPE_NORMAL;
			}

		}
	}

	c.type = CHUNK_TYPE_SOLID;

	_generateChunkBody(c);

	updateChunk(x, y);
}

void Terrain::updateChunk(unsigned int x, unsigned int y)
{
	std::vector<Vertex*> vertices(CHUNK_SIZE * CHUNK_SIZE * 4);

	_generateChunkMesh(_getChunk(x, y), (Vertex2D**) vertices.data(), nullptr);

	RenderEngine::modifyMesh("level_terrain", vertices, (x + y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE * 4);

	RenderEngine::load();
}

void Terrain::_generateChunks()
{
	_chunks.resize(_level->_chunksX * _level->_chunksY);

	for (unsigned int i = 0; i < _chunks.size(); i++) {
		Chunk c;

		c.x = i % _level->_chunksX;
		c.y = floor(i / _level->_chunksX);

		c.type = CHUNK_TYPE_SOLID;

		_generateChunkBody(c);

		std::vector<Tile> tiles(CHUNK_SIZE * CHUNK_SIZE);

		for (unsigned int j = 0; j < tiles.size(); j++) {
			Tile t;
			t.tileType = TILE_TYPE_SOLID;
			
			srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
			int r = rand() % 30;
			
			switch (r) {
			default: t.terrainOffset = 0; break;
			case 1: t.terrainOffset = 3; break;
			case 2: t.terrainOffset = 5; break;
			case 3: t.terrainOffset = 7; break;
			}

			t.x = c.x * CHUNK_SIZE + (j % CHUNK_SIZE);
			t.y = c.y * CHUNK_SIZE + (floor(j / CHUNK_SIZE));

			tiles[j] = t;
		}

		c.tiles = tiles;

		_chunks[i] = c;
	}

	//Decorate spawn
	Chunk& c_spawn = _getChunk(1, 1);
	c_spawn.type = CHUNK_TYPE_SPAWN;

	for (unsigned int i = 0; i < c_spawn.tiles.size(); i++) {
		srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		int r = rand() % 30;

		switch (r) {
		default: c_spawn.tiles[i].terrainOffset = 12; break;
		case 1: c_spawn.tiles[i].terrainOffset = 13; break;
		case 2: c_spawn.tiles[i].terrainOffset = 14; break;
		case 3: c_spawn.tiles[i].terrainOffset = 15; break;
		}

		c_spawn.tiles[i].tileType = TILE_TYPE_NORMAL;
	}

	c_spawn.tiles[(CHUNK_SIZE - 1) * CHUNK_SIZE + floor(CHUNK_SIZE / 2)].terrainOffset = 24;

	//Decorate end
	Chunk& c_end = _getChunk(_level->_chunksX - 2, _level->_chunksY - 2);
	c_end.type = CHUNK_TYPE_END;

	for (unsigned int i = 0; i < c_end.tiles.size(); i++) {
		srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		int r = rand() % 30;

		switch (r) {
		default: c_end.tiles[i].terrainOffset = 12; break;
		case 1: c_end.tiles[i].terrainOffset = 13; break;
		case 2: c_end.tiles[i].terrainOffset = 14; break;
		case 3: c_end.tiles[i].terrainOffset = 15; break;
		}

		c_end.tiles[i].tileType = TILE_TYPE_NORMAL;
	}
}

void Terrain::_generateMesh()
{
	Mesh mesh;
	
	std::vector<Vertex*> vertices(_level->_chunksX * CHUNK_SIZE * _level->_chunksY * CHUNK_SIZE * 4);

	mesh.indexCount = _level->_chunksX * CHUNK_SIZE * _level->_chunksY * CHUNK_SIZE * 6;
	
	std::vector<unsigned int> indices(mesh.indexCount);

	for (unsigned int i = 0; i < _chunks.size(); i++) {
		_generateChunkMesh(_chunks[i], (Vertex2D**) &vertices[i * CHUNK_SIZE * CHUNK_SIZE * 4], &indices[i * CHUNK_SIZE * CHUNK_SIZE * 6]);
	}

	mesh.vertices = vertices;

	mesh.indices = indices.data();

	mesh.shaderProgram = "ortho";

	GFXLibrary::registerMesh("level_terrain", mesh);

	RenderEngine::preloadMesh("level_terrain");

	RenderEngine::load();

	while (RenderEngine::remainingLoadEntries() > 0);

	getParent()->add(new Renderer(_level->_renderEngine, 0, "level_terrain", "terrain"));
	//getParent()->scale(1.0f / CHUNK_SIZE);
	//getParent()->transform.translate(- _level->_chunksX / 2, 1);
}

void Terrain::_generateChunkMesh(Chunk chunk, Vertex2D** vertices, unsigned int* indices)
{
	for (unsigned int i = 0; i < chunk.tiles.size(); i++) {

		float* texCoords = _generateTexCoords(chunk.tiles[i].terrainOffset);

		vertices[i * 4 + 0] = new Vertex2D(chunk.tiles[i].x, -((float)chunk.tiles[i].y), texCoords[0], texCoords[1]);

		vertices[i * 4 + 1] = new Vertex2D(chunk.tiles[i].x + 1, -((float)chunk.tiles[i].y), texCoords[2], texCoords[3]);

		vertices[i * 4 + 2] = new Vertex2D(chunk.tiles[i].x + 1, -((float)chunk.tiles[i].y) - 1, texCoords[4], texCoords[5]);

		vertices[i * 4 + 3] = new Vertex2D(chunk.tiles[i].x, -((float)chunk.tiles[i].y) - 1, texCoords[6], texCoords[7]);
		
		if (indices != nullptr) {
			indices[i * 6 + 0] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 0;
			indices[i * 6 + 1] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 1;
			indices[i * 6 + 2] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 3;
			indices[i * 6 + 3] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 3;
			indices[i * 6 + 4] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 1;
			indices[i * 6 + 5] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 2;
		}

		free(texCoords);
	}
}

float* Terrain::_generateTexCoords(unsigned int offset)
{	
	int tilesX = 12;
	int tilesY = 3;

	int offsetX = offset % tilesX;
	int offsetY = floor(offset / tilesX);

	float* coords = (float*) malloc(8 * sizeof(float));

	coords[0] = ((float)offsetX) / tilesX;
	coords[1] = ((float)offsetY) / tilesY;
	coords[2] = ((float)offsetX + 1) / tilesX;
	coords[3] = ((float)offsetY) / tilesY;
	coords[4] = ((float)offsetX + 1) / tilesX;
	coords[5] = ((float)offsetY + 1) / tilesY;
	coords[6] = ((float)offsetX) / tilesX;
	coords[7] = ((float)offsetY + 1) / tilesY;

	return coords;
}

void Terrain::_generateChunkBody(Chunk& c)
{
	b2BodyDef bodyDef;

	bodyDef.type = b2BodyType::b2_staticBody;
	bodyDef.position = b2Vec2(((float)CHUNK_SIZE) * (((float)c.x) + .5f), ((float)CHUNK_SIZE) * (((float)c.y) + .5f));

	b2PolygonShape shape;
	shape.SetAsBox(((float)CHUNK_SIZE) / 2, ((float)CHUNK_SIZE) / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	c.body = _level->_world->CreateBody(&bodyDef);

	c.body->CreateFixture(&fixture);
}

Chunk Terrain::getChunk(unsigned int x, unsigned int y)
{
	return _getChunk(x, y);
}

Chunk& Terrain::_getChunk(unsigned int x, unsigned int y)
{
	return _chunks[x + y * _level->_chunksX];
}

Tile Terrain::getTile(unsigned int x, unsigned int y)
{
	return _getTile(x, y);
}

Tile& Terrain::_getTile(unsigned int x, unsigned int y)
{
	Chunk& c = _getChunk(floor(((float)x) / CHUNK_SIZE), floor(((float)y) / CHUNK_SIZE));
	return c.tiles[(y % CHUNK_SIZE) * CHUNK_SIZE + (x % CHUNK_SIZE)];
}