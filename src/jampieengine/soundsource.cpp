#include "soundsource.h"

using namespace Jam;

SoundSource::SoundSource(): Sound(), Component() {}

SoundSource::~SoundSource() {}

void SoundSource::_update(double delta) {
	updateFade(delta);
}
