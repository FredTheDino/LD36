#pragma once

#include <vector>

#include "vertex.h"

namespace Jam
{
	struct Mesh {
		std::vector<Vertex*> vertices;
		unsigned int indexCount = 0;
		unsigned int* indices = nullptr;
		bool hasIndices() { return indexCount > 0; };
		std::string shaderProgram;
	};
}