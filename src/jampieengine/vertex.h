#pragma once

#include "glm/glm.hpp"

namespace Jam
{
	class Vertex
	{
	public:

		//Should return the number of attributes this vertex maintains
		virtual unsigned int numAttributes() = 0;

		//Should return the number of components in the specified attribute
		virtual unsigned int numComponents(unsigned int attr) = 0;

		//Should return the size of the attribute in bytes
		virtual unsigned int getAttributeSize(unsigned int attr) = 0;

		//Should return size of the fetched data in bytes
		virtual unsigned int getAttributeData(unsigned int attr, char* data) = 0;

		//Should return the data type of the components within the specified attribute
		virtual unsigned int getAttributeDataType(unsigned int attr) = 0;
	};
}