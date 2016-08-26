#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "component.h"
#include "renderer.h"
#include "entity.h"

namespace Jam
{
	struct Frame {
		unsigned int x;
		unsigned int y;
	};

	struct Animation {
		std::string spriteSheet;
		std::vector<Frame> frames;
		double speed;
	};

	class AnimationMachine : public Component
	{
	public:

		void _rootEnter() {};
		void _init() {};
		void _update(double delta);
		void _end() {};
		void _rootExit() {};

		void addAnimation(std::string tag, Animation animation);
		void enterAnimation(std::string tag) { _currentAnimation = tag; _offset = 0; };

	private:
		std::string _currentAnimation;

		unsigned int _offset = 0;

		std::unordered_map<std::string, Animation> _animations;
	};
}
/*
namespace std {
	template<> struct hash<Jam::Animation> {
		size_t operator()(const Jam::Animation & b) const {

			size_t hash = std::hash<std::string>()(b.spriteSheet);

			for (Frame frame : b.frames) {
				hash += frame.x * 233;
				hash += frame.y * 239;
			}

			return hash;
		}
	};
}*/