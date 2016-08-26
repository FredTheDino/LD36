#include "spatialsoundsource.h"
#include "entity.h"
#include "glm/glm.hpp"

Jam::SpatialSoundSource::SpatialSoundSource(): SpatialSound(), Component() {}

Jam::SpatialSoundSource::~SpatialSoundSource() {}

void Jam::SpatialSoundSource::_update(double delta) {
	updateFade(delta);
	
	//Get the transform, the delta positon / time is the velocity
	glm::vec3 pos = getParent()->getPosition();
	if (_position == pos) {
		if (_stationary) return;
		_stationary = true;
		_setVelocity(glm::vec3(0, 0, 0));
	} else {
		_stationary = false;
		_setVelocity((_position - pos) * (float) (1.0 / delta));
		_setPosition(pos);
	}
}
