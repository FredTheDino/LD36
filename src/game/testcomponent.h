#pragma once

#include <SDL2/SDL.h>
#include "loader.h"

#include "gamestate.h"
#include "gamestatelibrary.h"
#include "root.h"
#include "entity.h"
#include "node.h"
#include "component.h"
#include "audiohandler.h"
#include "audiolibrary.h"
#include "soundsource.h"
#include "audiolistener.h"

class TestComponent: public Jam::Component {
public:
	void _begin() {
		Jam::AudioHandler::preload("fred", "jungle.wav");
		Jam::AudioHandler::preload("test", "audio.wav");
		Jam::AudioListener::setMasterVolume(0.5);
		Jam::AudioListener::setPosition(0, 0, 0);
	}

	void _update(double delta) {
		if (Jam::AudioHandler::ready() && Jam::InputHandler::keyPressed("t_reset")) {
			Jam::SoundSource* source = _getParent()->get<Jam::SoundSource>();
			if (source) {
				source->stop();
				source->setBuffer("fred");
				source->play();
				//source->setGain(0.5);
				//source->play("test");
				//source->fadePitch(2, 2);
			}
		}
	}

	void _end() {

	}

	void reset() {
		i = 0;
	}

private:
	int i;
};