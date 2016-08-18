#include "spatialsoundsource.h"

Jam::SpatialSoundSource::SpatialSoundSource(): SpatialSound(), Component() {}

Jam::SpatialSoundSource::~SpatialSoundSource() {}

void Jam::SpatialSoundSource::_update(double delta) {
	updateFade(delta);
	
	//Get the transform, the delta positon / time is the velocity
	Transform* t = &_getParent()->transform;
	_setVelocity((_position - t->position) * (float) (1.0 / delta));
	_setPosition(t->position);
}
