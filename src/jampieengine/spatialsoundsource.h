#pragma once

#include "spatialsound.h"
#include "component.h"

namespace Jam {
	class SpatialSoundSource : public SpatialSound, public Component {
	public:
		SpatialSoundSource();
		~SpatialSoundSource();

		//Un implemented component functions
		void _begin() {};
		void _end() {};

		void _update(double delta);
	};
}