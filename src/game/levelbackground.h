#pragma once

#include <stdlib.h>
#include <chrono>

#include "component.h"
#include "mesh.h"
#include "vertex2d.h"
#include "gfxlibrary.h"
#include "entity.h"

#include "level.h"

class Level;

enum ChunkType {
	CHUNK_TYPE_SOLID,
	CHUNK_TYPE_NORMAL,
	CHUNK_TYPE_SPAWN,
	CHUNK_TYPE_END
};

struct Tile {
	unsigned int x;
	unsigned int y;
	unsigned int terrainOffset = 0;
};

struct Chunk {
	unsigned int x;
	unsigned int y;
	ChunkType type;
	std::vector<Tile> tiles;
};

class LevelBackground : public Jam::Component
{
public:
	LevelBackground(Level* level);

	static const unsigned int CHUNK_SIZE;

	void _rootEnter() {};
	void _init();
	void _update(double delta) {};
	void _end() {};
	void _rootExit() {};

private:

	Level* _level;

	std::vector<Chunk> _chunks;

	void _generateChunks();

	void _generateMesh();

	void _generateChunkMesh(Chunk chunk, Jam::Vertex2D** vertices, unsigned int* indices);

	float* _generateTexCoords(unsigned int offset);

	Chunk& _getChunk(unsigned int x, unsigned int y);

};