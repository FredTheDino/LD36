#pragma once

#include "glm/glm.hpp"

namespace Jam {

	//The key states for digital input (multiple can be active
	enum KeyState {
		//If not helt down
		UP = 0x1,
		//If held down
		DOWN = 0x2,
		//If released this frame
		RELEASED = 0x4,
		//If pressed this frame
		PRESSED = 0x8
	};

	struct InputData {
		//The state of the key/button
		short status = KeyState::UP;
		//The value of the axis normalized between -1 and 1
		double axis = 0.0;
	};

	struct MousePos {
		glm::vec2 position;
		glm::vec2 delta;
	};

	//A simple input data structure with a simple function for easy equallity checks
	struct InputBinding {

		//Ease of use constructor
		InputBinding() {}
		InputBinding(bool isMouseButton, int key):
			isMouseButton(isMouseButton), isScancode(false), dev(-1), mods(0), code(key) {}

		InputBinding(bool isScancode, int dev, int mods, int code):
			isMouseButton(false), isScancode(isScancode), dev(-1), mods(mods), code(code) {}

		InputBinding(int dev, int axis):
			isMouseButton(false), isScancode(false), dev(dev), mods(axis), code(0) {}

		//Ease of use equallity check for linear search
		bool operator== (const InputBinding& data) const {
			return
				data.isMouseButton == isMouseButton &&
				data.isScancode == isScancode &&
				data.dev == dev &&
				data.mods == mods &&
				data.code == code;
		}

		//If the binding given is a mouse button
		bool isMouseButton;
		//If code is a scancode or a keycode
		bool isScancode;
		//Which device this is registerd to, -1 is keyboard the rest are controllers
		int dev;
		//Any modifiers (alt, shift, etc...) for this input event, requiers a keyboard
		int mods;
		//The key/button/axis-code
		int code;
	};
}

//Custom hash function, to allow it to be inserted in a unorderd_map
namespace std {
	template<> struct hash<Jam::InputBinding> {
		size_t operator()(const Jam::InputBinding & b) const {

			size_t hash = 0;

			if (b.isMouseButton) hash += 1;
			hash *= 37;
			if (b.isScancode) hash += 1;
			hash *= 37;
			hash += b.dev;
			hash *= 37;
			hash += b.mods;
			hash *= 37;
			hash += b.code;

			return hash;
		}
	};
}