#include "entity.h"

namespace Jam {
	
	Entity::Entity() {}

	Entity::~Entity() {
		for (size_t i = 0; i < _components.size(); i++) {
			_components[i]->_end();
		}

		for (size_t i = 0; i < _components.size(); i++) {
			delete _components[i];
		}
		_components.clear();
	}

	template<class T>
	bool Entity::add(T component) {
		//Return if that type allready exists
		if (get<T>()) { return false; }

		//Create a local copy of it on the heap
		component = new T(component);
		component->_setParent(*this);
		component->_begin();

		_components.push_back(component);
		return true;
	}

	template <class T>
	T* Entity::get() {
		
		T* component = nullptr;

		for (size_t i = 0; i < _components.size(); i++) {
			component = dynamic_cast<T*>(_components[i]);
			if (component) {
				break;
			}
		}

		return component;
	}

	template<class T>
	bool Entity::remove() {

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

	void Entity::setAll(bool active) {
		for (size_t i = 0; i < _components.size(); i++) {
			_components[i]->setActive(active);
		}
	}

	void Entity::toggleAll() {
		for (size_t i = 0; i < _components.size(); i++) {
			_components[i]->toggleActive();
		}
	}


	template<class T>
	bool Entity::isActive() {

		bool active = false;
		for (size_t i = 0; i < _components.size(); i++) {
			if (dynamic_cast<T*>(_components[i])) {
				active = _components[i]->_isActive;
			}
		}

		return active;
	}

	template<class T>
	void Entity::setActive(bool active) {
		for (size_t i = 0; i < _components.size(); i++) {
			if (dynamic_cast<T*>(_components[i])) {
				_components[i]->setActive(active);
			}
		}
	}

	template<class T>
	void Entity::toggle() {
		for (size_t i = 0; i < _components.size(); i++) {
			if (dynamic_cast<T*>(_components[i])) {
				_components[i]->toggle();
			}
		}
	}

	void Entity::_update(float delta) {
		for (size_t i = 0; i < _components.size(); i++) {
			_components[i]->_update(delta);
		}
	}
}