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

	}

	void _update(double delta) {

	}

	void _end() {

	}

	void reset() {
		i = 0;
	}

private:
	int i;
};