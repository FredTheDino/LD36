#include "vertex2d.h"

using namespace Jam;

Vertex2D::Vertex2D(float x, float y, float s, float t)
{
	pos.x = x;
	pos.y = y;
	texCoords.x = s;
	texCoords.y = t;
}

unsigned int Vertex2D::numAttributes()
{
	return 2;
}

unsigned int Vertex2D::numComponents(unsigned int attr)
{
	return 2;
}

unsigned int Vertex2D::getAttributeSize(unsigned int attr)
{
	return numComponents(attr) * sizeof(float);
}

unsigned int Vertex2D::getAttributeData(unsigned int attr, char* data)
{
	float vec[2];

	switch (attr) {
	case 0: vec[0] = pos.x; vec[1] = pos.y; break;
	case 1: vec[0] = texCoords.x; vec[1] = texCoords.y; break;
	}

	char* temp = (char*) &vec[0];

	for (unsigned int i = 0; i < getAttributeSize(attr); i++) {
		data[i] = temp[i];
	}

	return getAttributeSize(attr);
}

unsigned int Vertex2D::getAttributeDataType(unsigned int attr)
{
	return GL_FLOAT;
}