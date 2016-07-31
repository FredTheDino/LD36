#pragma once

#include <unordered_map>

#include "glmesh.h"

namespace Jam
{
	class GLLibrary
	{
	public:

		void registerMesh(std::string tag, GLMesh mesh) { _meshRegistry.insert(std::make_pair(tag, mesh)); };

	private:
		static std::unordered_map<std::string, GLMesh> _meshRegistry;
	};
}