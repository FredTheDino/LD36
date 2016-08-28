#pragma once

#include "GL/glew.h"

#include "mesh.h"

#include "debug.h"

namespace Jam
{
	class GLMesh
	{
	public:
		GLMesh(Mesh mesh);
		~GLMesh();

		void draw();

		void modifyData(unsigned int offset, std::vector<Vertex*> vertices);

	private:

		bool _usingIndices;

		unsigned int _vertexCount;
		unsigned int _indexCount;

		GLuint _vao = 0;

		GLuint _ibo = 0;

		GLsizei _vboCount = 0;
		std::vector<GLuint> _vboList;

	};
}