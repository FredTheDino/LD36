#include "entity.h"

namespace Jam {
	
	Entity::Entity() {
	
	}

	Entity::~Entity() {

	}

	template<class T>
	bool Entity::addComponent(T component) {
		//Return if that type allready exists
		if (getComponent(component._type)) { return false; }

		_components.insert({component._type, component});
		return true;
	}

	template <class T>
	T* Entity::getComponent(ComponentTypes type) {
		auto it = _components.find(type);
		
		if (it == _components.end()) {
			return nullptr;
		}

		return &it->second;
		
	}

}