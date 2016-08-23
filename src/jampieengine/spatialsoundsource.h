#pragma once

#include "spatialsound.h"
#include "component.h"

namespace Jam {
	class SpatialSoundSource : public SpatialSound, public Component {
	public:
		SpatialSoundSource();
		~SpatialSoundSource();

		//Un implemented component functions
		void _rootEnter() {};
		void _init() {};
		void _end() {};
		void _rootExit() {};

		void _update(double delta);
	
	private:
		bool _stationary = false;
	};
}