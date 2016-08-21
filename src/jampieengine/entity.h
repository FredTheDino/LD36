#pragma once

#include <type_traits>

#include "component.h"
#include "transform.h"
#include "node.h"

#include <unordered_map>

namespace Jam
{
	class Component;
	
	class Entity : Node
	{
	public:
		Entity();
		~Entity();


		//Adds a component, returns true if didn't exitst, false otherwise
		template <class T>
		bool add(T* component)
		{
			//Check if the added class is a component
			//static_assert(std::is_base_of<Component, T>::value, "Can only add components to entity");

			//Return if that type allready exists
			if (get<T>()) { return false; }

			//Create a local copy of it on the heap
			component = new T(*component);
			component->_setParent(this);
			component->_begin();

			_components.push_back(component);
			return true;
		}

		//Returns a pointer to the component, null pointer otherwise.
		template <class T>
		T* get()
		{
			T* component = nullptr;

			for (size_t i = 0; i < _components.size(); i++) {
				component = dynamic_cast<T*>(_components[i]);
				if (component) {
					break;
				}
			}

			return component;
		}

		//Returns true if deleteion succseded
		template <class T>
		bool remove()
		{
			for (size_t i = 0; i < _components.size(); i++) {
				if (dynamic_cast<T*>(_components[i])) {
					_components[i]->_end();
					delete _components[i];
					_components.erase(_components.begin() + i);
					return true;
				}
			}

			return false;
		}

		//Returns is the component is active
		template <class T>
		bool isActive()
		{
			bool active = false;
			for (size_t i = 0; i < _components.size(); i++) {
				if (dynamic_cast<T*>(_components[i])) {
					active = _components[i]->_isActive;
				}
			}

			return active;
		}

		//Sets the component should be active
		template <class T>
		void setActive(bool active)
		{
			for (size_t i = 0; i < _components.size(); i++) {
				if (dynamic_cast<T*>(_components[i])) {
					_components[i]->setActive(active);
				}
			}
		}

		//Toggles the specified componet
		template <class T>
		void toggle()
		{
			for (size_t i = 0; i < _components.size(); i++) {
				if (dynamic_cast<T*>(_components[i])) {
					_components[i]->toggle();
				}
			}
		}

		//Sets all components to eiter active or not
		void setAll(bool active);

		//Toggles all componet
		void toggleAll();

		//The transform of this entity
		Transform transform;

		//The update function
		void update(double delta);

	private:

		//The vector holding all the components
		std::vector<Component*> _components;
	};
}