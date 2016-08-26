#include "animation.h"

using namespace Jam;

void AnimationMachine::addAnimation(std::string tag, Animation animation)
{
	_animations.insert(std::make_pair(tag, animation));

	if (_animations.size() == 1)
		_currentAnimation = tag;
}

void AnimationMachine::_update(double delta)
{
	if (!isActive())
		return;

	static double stack;
	stack += delta;

	if (stack >= 1.0 / _animations.at(_currentAnimation).speed) {
		_offset++;
		_offset %= _animations.at(_currentAnimation).frames.size();
		
		if (getParent()->has<Renderer>())
			getParent()->get<Renderer>()->setTexture(_animations.at(_currentAnimation).spriteSheet,
				_animations.at(_currentAnimation).frames[_offset].x, _animations.at(_currentAnimation).frames[_offset].y);
		
		stack = 0;
	}
}