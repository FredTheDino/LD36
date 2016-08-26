#pragma once

#include "gui.h"
#include "Box2D/Box2D.h"

namespace Jam {

	class GUIInput : public GUIElement {
	public:
		//NOTE: The button is not stored using that refference, it is copied. 
		GUIInput(RenderEngine* engine, int layer, float anchorX, float anchorY,
				 std::string texture, b2Shape* shape);
		~GUIInput();

		void setOnHighlight(void(*func)(GUIInput*));
		void setOnDehighlight(void(*func)(GUIInput*));
		void setOnPress(void(*func)(GUIInput*));
		void setOnRelease(void(*func)(GUIInput*));

		virtual void _update(double delta);

		//NOTE: The shape does NOT scale with the button. 
		//You'll have to re create it.
		virtual void setShape(b2Shape* shape);

	protected:

		virtual void _highlight() = 0;
		virtual void _dehighlight() = 0;
		virtual void _down() = 0;
		virtual void _up() = 0;

		void(*_onHighlight)(GUIInput*) = nullptr;
		void(*_onDehighlight)(GUIInput*) = nullptr;
		void(*_onPress)(GUIInput*) = nullptr;
		void(*_onRelease)(GUIInput*) = nullptr;

		b2Shape* _shape = nullptr;

		bool _hoverd = false;
		bool _pressed = true;
	};
}