#pragma once

#include "renderer.h"
#include "glm/glm.hpp"
#include "renderengine.h"

namespace Jam {

	class Transform;

	class GUIElement : public Renderer{
	public:
		GUIElement(RenderEngine* engine, int layer, float anchorX, float anchorY, 
			std::string texture);
		~GUIElement();

		//Initalize the
		virtual void _init();

		//Initalize
		virtual void _update() {};
		virtual void _end() {};

		//Does this really need a comment
		virtual void draw();


		void setAnchor(glm::vec2 anchor);
		void setAnchor(float x, float y = 0.0);

		glm::vec2 getAnchor();

	protected:

		Transform _calculateTransform();

		bool _isFader = false;

		glm::vec2 _anchor;

	};
}