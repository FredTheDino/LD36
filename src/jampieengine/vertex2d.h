#pragma once

#include <iostream>

#include "GL/glew.h"

#include "vertex.h"

namespace Jam
{
	class Vertex2D : Vertex
	{
	public:

		Vertex2D(float x = 0, float y = 0, float s = 0, float t = 0);

		glm::vec2 pos;
		glm::vec2 texCoords;

		//Should return the number of attributes this vertex maintains
		unsigned int numAttributes();

		//Should return the number of components in the specified attribute
		unsigned int numComponents(unsigned int attr);

		//Should return the size of the attribute in bytes
		unsigned int getAttributeSize(unsigned int attr);

		//Should return size of the fetched data in bytes
		unsigned int getAttributeData(unsigned int attr, char* data);

		//Should return the data type of the components within the specified attribute
		unsigned int getAttributeDataType(unsigned int attr);
	};
}