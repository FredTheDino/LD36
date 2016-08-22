#pragma once

#include "component.h"
#include "audiohandler.h"
#include "spatialsoundsource.h"
#include "audiohandler.h"
#include "inputhandler.h"

class AudioComponentTest: public Jam::Component {
public:
	void _init() {
		Jam::AudioHandler::preload("fred", "jungle.wav");
		Jam::AudioHandler::preload("test", "audio.wav");
		Jam::SpatialSoundSource* s = new Jam::SpatialSoundSource();
		getParent()->add(s);
	}

	void _update(double delta) {
		if (Jam::AudioHandler::ready() && Jam::InputHandler::keyPressed("t_play")) {
			Jam::SpatialSoundSource* source = getParent()->get<Jam::SpatialSoundSource>();
			if (source) {
				if (!source->isPlaying()) {
					source->setGain(1);
					source->setLooping(true);
					source->play("test");
				} else {
					source->pause();
				}
			}
		}
		
		getParent()->transform.rotateZ(delta);

	}

	void _end() {
		Jam::AudioHandler::unload("fred");
		Jam::AudioHandler::unload("test");
	}
};