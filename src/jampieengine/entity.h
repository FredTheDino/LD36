#pragma once

#include "component.h"
#include "transform.h"

#include <unordered_map>

namespace Jam {
	
	class Entity {
	public:
		Entity();
		~Entity();


		//Adds a component, returns true if didn't exitst, false otherwise
		template <class T>
		bool add(T component);

		//Returns a pointer to the component, null pointer otherwise.
		template <class T>
		T* get();

		//Returns true if deleteion succseded
		template <class T>
		bool remove();

		//Returns is the component is active
		template <class T>
		bool isActive();

		//Sets the component should be active
		template <class T>
		void setActive(bool active);

		//Toggles the specified componet
		template <class T>
		void toggle();

		//Sets all components to eiter active or not
		void setAll(bool active);

		//Toggles all componet
		void toggleAll();

		//The transform of this entity
		Transform transform;

	private:

		//The update function
		void _update(float delta);

		//The vector holding all the components
		std::vector<Component*> _components;
	};
}