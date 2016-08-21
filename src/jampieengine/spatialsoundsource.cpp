#include "spatialsoundsource.h"

Jam::SpatialSoundSource::SpatialSoundSource(): SpatialSound(), Component() {}

Jam::SpatialSoundSource::~SpatialSoundSource() {}

void Jam::SpatialSoundSource::_update(double delta) {
	updateFade(delta);
	
	//Get the transform, the delta positon / time is the velocity
	Transform* t = &getParent()->transform;
	if (_position == t->position) {
		if (_stationary) return;
		_stationary = true;
		_setVelocity(glm::vec3(0, 0, 0));
	} else {
		_stationary = false;
		_setVelocity((_position - t->position) * (float) (1.0 / delta));
		_setPosition(t->position);
	}
}
