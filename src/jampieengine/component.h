#pragma once

namespace Jam {
	class Entity;

	enum ComponentTypes {
		COMPONENT,
		SOUND_LISTENER,
		SOUND_SOURCE,
	};

	class Component {
	public:
		Component() {};
		~Component() {};

		//Sets weather this component is active or not
		void setActive(bool active);
		//Toggles this components active state
		void toggleActive();
		//Returns if this component is active
		bool isActive();

	protected:
		
		//A functions that is ment to initalize everything 
		// after the parent has been assigned.
		virtual void _begin() = 0;

		//The update call for this component, is only called if active
		virtual void _update(float delta) = 0;

		//A functions that is ment to deinitalize everything 
		// before the parent is destroyed.
		virtual void _end() = 0;

		inline Entity* _getParent();

	private:
		//If this object is active
		bool _isActive = true;

		//Sets the entity this object is pointing at
		void _setParent(Entity& parent);

		//A pointer to the parent
		Entity* _parent = nullptr;

		friend Entity;
	};
}