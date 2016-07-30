#pragma once

#include "component.h"

#include <unordered_map>

namespace Jam {
	
	class Entity {
	public:
		Entity();
		~Entity();

		template <class T>
		bool addComponent(T component);

		template <class T>
		T* getComponent(ComponentTypes type);

	private:

		std::unordered_map<ComponentTypes, Component> _components;

	};
}