#pragma once

#include "renderer.h"
#include "material.h"
#include "glm/glm.hpp"
#include "renderengine.h"

namespace Jam {

	class GUI : public Renderer{
	public:
		GUI(RenderEngine* engine, int layer, Material material, float anchorX, float anchorY);
		~GUI();

		virtual void draw();

		void setAnchor(glm::vec2 anchor);
		void setAnchor(float x, float y = 0.0);

		glm::vec2 getAnchor();

	protected:

		bool _isFader = false;

	private:

		glm::vec2 _anchor;

	};
}