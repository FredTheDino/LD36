#pragma once

#include "guiinput.h"

namespace Jam {

	class GUIButton : public GUIInput {
	public:
		GUIButton(RenderEngine* engine, int layer, float anchorX, float anchorY,
				  std::string texture, b2Shape* shape);
		~GUIButton();

		virtual void _init();

		virtual bool isDown();

	protected:
		virtual void _highlight();
		virtual void _dehighlight();
		virtual void _down();
		virtual void _up();

		bool _isDown;
	};
}