#pragma once

#include "guibutton.h"
#include "material.h"

namespace Jam {

	class GUIToggle : public GUIButton {
	public:
		GUIToggle(RenderEngine* engine, int layer, float anchorX, float anchorY,
				  std::string on, std::string off, b2Shape* shape);
		~GUIToggle();

	private:

		std::string _texOn;
		std::string _texOff;

		virtual void _highlight();
		virtual void _dehighlight();
		virtual void _down();
		virtual void _up();

	};
}