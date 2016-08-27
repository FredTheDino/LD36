#include "levelbackground.h"

using namespace Jam;

const unsigned int LevelBackground::CHUNK_SIZE = 3;

LevelBackground::LevelBackground(Level* level)
	: _level(level)
{
	
}

void LevelBackground::_init()
{
	_generateChunks();
	_generateMesh();
}

void LevelBackground::_generateChunks()
{
	_chunks.resize(_level->_chunksX * _level->_chunksY);

	for (unsigned int i = 0; i < _chunks.size(); i++) {
		Chunk c;

		c.x = i % _level->_chunksX;
		c.y = floor(i / _level->_chunksX);

		c.type = CHUNK_TYPE_SOLID;

		std::vector<Tile> tiles(CHUNK_SIZE * CHUNK_SIZE);

		for (unsigned int j = 0; j < tiles.size(); j++) {
			Tile t;
			
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
	c_spawn.type = CHUNK_TYPE_SOLID;

	for (unsigned int i = 0; i < c_spawn.tiles.size(); i++) {
		srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		int r = rand() % 30;

		switch (r) {
		default: c_spawn.tiles[i].terrainOffset = 12; break;
		case 1: c_spawn.tiles[i].terrainOffset = 13; break;
		case 2: c_spawn.tiles[i].terrainOffset = 14; break;
		case 3: c_spawn.tiles[i].terrainOffset = 15; break;
		}
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
	}
}

void LevelBackground::_generateMesh()
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

void LevelBackground::_generateChunkMesh(Chunk chunk, Vertex2D** vertices, unsigned int* indices)
{
	for (unsigned int i = 0; i < chunk.tiles.size(); i++) {

		float* texCoords = _generateTexCoords(chunk.tiles[i].terrainOffset);

		vertices[i * 4 + 0] = new Vertex2D(chunk.tiles[i].x, -((float)chunk.tiles[i].y), texCoords[0], texCoords[1]);

		vertices[i * 4 + 1] = new Vertex2D(chunk.tiles[i].x + 1, -((float)chunk.tiles[i].y), texCoords[2], texCoords[3]);

		vertices[i * 4 + 2] = new Vertex2D(chunk.tiles[i].x + 1, -((float)chunk.tiles[i].y) - 1, texCoords[4], texCoords[5]);

		vertices[i * 4 + 3] = new Vertex2D(chunk.tiles[i].x, -((float)chunk.tiles[i].y) - 1, texCoords[6], texCoords[7]);
		
		indices[i * 6 + 0] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 0;
		indices[i * 6 + 1] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 1;
		indices[i * 6 + 2] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 3;
		indices[i * 6 + 3] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 3;
		indices[i * 6 + 4] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 1;
		indices[i * 6 + 5] = ((chunk.x + chunk.y * _level->_chunksX) * CHUNK_SIZE * CHUNK_SIZE + i) * 4 + 2;
		
		free(texCoords);
	}
}

float* LevelBackground::_generateTexCoords(unsigned int offset)
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

Chunk& LevelBackground::_getChunk(unsigned int x, unsigned int y)
{
	return _chunks[x + y * _level->_chunksX];
}