#pragma once
#include "component.h"
#include "renderer.h"
#include "material.h"

namespace Jam {

	class TrapComponent: public Jam::Component {
	public:
		TrapComponent(Jam::RenderEngine* engine, Jam::Material material, std::string trigger, float coolDown, float fireTime, glm::vec2 min, glm::vec2 max);
		~TrapComponent();

		virtual void _init();
		virtual void _update(double delta);
		virtual void _end();


		virtual void _rootEnter();
		virtual void _rootExit();

		virtual void _fire() {
			std::cout << "FIRE!" << std::endl;
		}

		virtual void _reset() {
			std::cout << "Reset" << std::endl;
		}

	protected:
		float _t = 0;
		float _coolDown = 0;
		float _fireTime = 0;

		bool _isFireing = false;

		std::string _trigger = "";

		Jam::RenderEngine* _engine = nullptr;

		Jam::Material _material;
		glm::vec2 _min, _max;
	};
}