#pragma once

#include <stdlib.h>
#include <chrono>

#include "component.h"
#include "mesh.h"
#include "vertex2d.h"
#include "gfxlibrary.h"
#include "entity.h"
#include "inputhandler.h"

#include "level.h"

class Level;

enum ChunkType {
	CHUNK_TYPE_SOLID,
	CHUNK_TYPE_NORMAL,
	CHUNK_TYPE_SPAWN,
	CHUNK_TYPE_END
};

enum TileType {
	TILE_TYPE_SOLID,
	TILE_TYPE_NORMAL,
	TILE_TYPE_EXIT,
	TILE_TYPE_LADDER
};

struct Tile {
	unsigned int x;
	unsigned int y;
	unsigned int terrainOffset = 0;
	TileType tileType;
};

struct Chunk {
	unsigned int x;
	unsigned int y;
	ChunkType type;
	std::vector<Tile> tiles;
	b2Body* body;
};

class Terrain : public Jam::Component
{
public:
	Terrain(Level* level);

	static const unsigned int CHUNK_SIZE;

	void _rootEnter() {};
	void _init();
	void _update(double delta);
	void _end() {};
	void _rootExit() {};

	void buyChunk(unsigned int x, unsigned int y);
	void sellChunk(unsigned int x, unsigned int y);

	void updateChunk(unsigned int x, unsigned int y);

	Chunk getChunk(unsigned int x, unsigned int y);

	Tile getTile(unsigned int x, unsigned int y);

private:

	Level* _level;

	std::vector<Chunk> _chunks;

	void _generateChunks();

	void _generateMesh();

	void _generateChunkMesh(Chunk chunk, Jam::Vertex2D** vertices, unsigned int* indices);

	float* _generateTexCoords(unsigned int offset);
	
	void _generateChunkBody(Chunk& c);

	Chunk& _getChunk(unsigned int x, unsigned int y);
};