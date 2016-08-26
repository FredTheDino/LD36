#pragma once

#include "guifader.h"
#include "guiinput.h"

namespace Jam {
	class GUISlider : public GUIInput {
	public:
		GUISlider(RenderEngine* engine, int layer, float anchorX, float anchorY,
				  std::string on, std::string off, std::string value, b2Shape* shape);
		~GUISlider();

		void setValue(float value);
		float getValue();

		virtual void setShape(b2Shape* shape);

		virtual void _update(double delta);

		virtual void draw();

	private:
		virtual void _highlight();
		virtual void _dehighlight();
		virtual void _down();
		virtual void _up();

		void _computeSliderPosition();

		Material _materialOff;
		Material _materialValue;
		
		float _minXOffset = 0;

		float _invertedWidth = 0;

		bool _isHeld = false;

		float _value;
	};
}