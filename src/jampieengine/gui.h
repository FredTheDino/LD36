#pragma once

#include "renderer.h"
#include "material.h"
#include "glm/glm.hpp"
#include "renderengine.h"

namespace Jam {

	class GUIElement : public Renderer{
	public:
		GUIElement(RenderEngine* engine, int layer, float anchorX, float anchorY, 
			Material material);
		~GUIElement();

		virtual void _init();

		virtual void draw();

		void setAnchor(glm::vec2 anchor);
		void setAnchor(float x, float y = 0.0);

		glm::vec2 getAnchor();

	protected:

		bool _isFader = false;

		glm::vec2 _anchor;

	};
}