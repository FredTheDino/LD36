#pragma once

#include <type_traits>

#include "component.h"
#include "transform.h"
#include "node.h"

#include <vector>

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
			static_assert(std::is_base_of<Component, T>::value, "Can only add components to entity");

			//Return if that type allready exists
			if (get<T>()) { return false; }

			//Create a local copy of it on the heap
			component->_setParent(this);
			component->_init();

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

		//Returns true if the specified component exists on this entity
		template <class T>
		bool has()
		{
			return get<T>() != nullptr;
		}

		//Returns true if deleteion succseded
		template <class T>
		bool remove()
		{
			//Since we exit after we find our element, 
			// we don't care if the pointers are jumbled
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
			for (size_t i = 0; i < _components.size(); i++) {
				if (dynamic_cast<T*>(_components[i])) {
					return _components[i]->_isActive;
				}
			}
			return false;
		}

		//Sets the component should be active
		template <class T>
		void setActive(bool active)
		{
			for (size_t i = 0; i < _components.size(); i++) {
				if (dynamic_cast<T*>(_components[i])) {
					_components[i]->setActive(active);
					return;
				}
			}
		}

		//Toggles the specified componet
		template <class T>
		void toggle()
		{
			for (size_t i = 0; i < _components.size(); i++) {
				if (dynamic_cast<T*>(_components[i])) {
					_components[i]->toggleActive();
					return;
				}
			}
		}

		//Sets all components to eiter active or not
		void setAll(bool active);

		//Toggles all componet
		void toggleAll();

		//Move the entity
		void move(float x, float y = 0.0, float z = 0.0);
		void move(glm::vec3 dpos);

		//Sets the position
		void setPosition(glm::vec3 newPos);

		//Return the position
		glm::vec3 getPosition();

		//Scale	
		void scale(float scalar);
		void scale(float x, float y, float z = 1.0);

		//Set the scale
		void setScale(glm::vec3 scale);

		//Returns the scale 
		glm::vec3 getScale();

		//Rotate
		void rotate(float z);
		void rotate(float x, float y, float z = 0.0f);

		//Set the rotation
		void setRotation(glm::vec3 newRotation);

		//Get the rotation
		glm::vec3 getRotation();
		
		//Get the transformation matrix
		glm::mat4 getTransformationMatrix();

		//Returns the transform
		Transform getTransform();

		//The update function
		void update(double delta);

		void _rootEnter();
		void _rootExit();

		//The transform of this entity
		Transform transform;

	private:

		//The vector holding all the components
		std::vector<Component*> _components;
	};
}