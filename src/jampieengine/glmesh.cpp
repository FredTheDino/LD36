#include "glmesh.h"

using namespace Jam;

GLMesh::GLMesh(Mesh& mesh)
{
	//Generate VAO
	glGenVertexArrays(1, &_vao);

	if (_vao <= 0) {
		Debug::err("Failed to generate VAO", _vao);
	}

	//Bind VAO
	glBindVertexArray(_vao);

	Vertex* vert = mesh.vertices[0];

	//Fetching vertex information from mesh
	_vertexCount = mesh.vertices.size();
	_vboCount = vert->numAttributes();
	
	//Setting IBO variables
	_usingIndices = mesh.hasIndices();
	_indexCount = mesh.indexCount;

	//Generate IBO and associate it with VAO if applicable
	if (_usingIndices) {
		glGenBuffers(1, &_ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		std::cout << _ibo << std::endl;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(unsigned int), mesh.indices, GL_STATIC_DRAW);
	}
	_vboList.resize(_vboCount);

	//Create VBOs
	glGenBuffers(vert->numAttributes(), _vboList.data());

	//Generate VBO for each vertex attribute
	for (unsigned int i = 0; i < vert->numAttributes(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, _vboList[i]);

		std::vector<char> data(_vertexCount * vert->getAttributeSize(i));
		for (unsigned int j = 0; j < _vertexCount; j++) {
			mesh.vertices[j]->getAttributeData(i, &data[j * vert->getAttributeSize(i)]);
		}

		glBufferData(GL_ARRAY_BUFFER, data.size(), &data.front(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, vert->numComponents(i), vert->getAttributeDataType(i), GL_FALSE, 0, 0);
	}

	glBindVertexArray(0);
}

void GLMesh::draw()
{
	glBindVertexArray(_vao);

	if (_usingIndices) {
		glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, nullptr);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
	}
	glBindVertexArray(0);
}

GLMesh::~GLMesh()
{
	glDeleteBuffers(_vboCount, _vboList.data());
	glDeleteBuffers(1, &_ibo);
	glDeleteVertexArrays(1, &_vao);
}