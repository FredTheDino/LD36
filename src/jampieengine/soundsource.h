#pragma once

#include "component.h"
#include "soundfade.h"
#include "sound.h"

namespace Jam {
	class SoundSource: public Sound, public Component {
	public:
		SoundSource();
		~SoundSource();
		
		//Empty virtual functions
		virtual void _begin() {};
		virtual void _end() {};

		//The update call for this component, is only called if active
		virtual void _update(double delta);
	};
}