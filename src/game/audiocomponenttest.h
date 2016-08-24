#pragma once

#include "component.h"
#include "audiohandler.h"
#include "spatialsoundsource.h"
#include "audiohandler.h"
#include "inputhandler.h"

class AudioComponentTest: public Jam::Component {
public:

	void _rootEnter() {};

	void _init() {
		Jam::AudioHandler::preload("fred", "jungle.wav");
		Jam::AudioHandler::preload("test", "audio.wav");
		Jam::SpatialSoundSource* s = new Jam::SpatialSoundSource();
		getParent()->add(s);

		Jam::InputHandler::registerInput("e_left", Jam::InputBinding(true, SDLK_a));
		Jam::InputHandler::registerInput("e_right", Jam::InputBinding(true, SDLK_d));
		Jam::InputHandler::registerInput("e_up", Jam::InputBinding(true, SDLK_w));
		Jam::InputHandler::registerInput("e_down", Jam::InputBinding(true, SDLK_s));
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
		if (Jam::InputHandler::keyDown("e_left"))
			getParent()->move(-delta);
		if (Jam::InputHandler::keyDown("e_right"))
			getParent()->move(delta);
		if (Jam::InputHandler::keyDown("e_up"))
			getParent()->move(0.0, delta);
		if (Jam::InputHandler::keyDown("e_down"))
			getParent()->move(0.0, -delta);
		
		getParent()->rotate(delta);
		static float t = 0;
		t += delta;
		getParent()->move(sin(t) * 0.01, cos(t) * 0.01); //CRASHES
	}

	void _end() {
		Jam::AudioHandler::unload("fred");
		Jam::AudioHandler::unload("test");
	}

	void _rootExit() {};
};