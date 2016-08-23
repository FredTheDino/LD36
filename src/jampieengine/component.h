#pragma once

namespace Jam {
	
	//Forward declaration
	class Entity;

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

		//This function is called when the parent's root is entered
		virtual void _rootEnter() = 0;

		//A functions that is ment to initalize everything 
		// after the parent has been assigned.
		virtual void _init() = 0;

		//The update call for this component, is only called if active
		virtual void _update(double delta) = 0;

		//A functions that is ment to deinitalize everything 
		// before the parent is destroyed.
		virtual void _end() = 0;

		//This function is called when the parent's root is exited
		virtual void _rootExit() = 0;

		//Get the parent entity
		Entity* getParent();

	private:
		//Sets the entity this object is pointing at
		void _setParent(Entity* parent);

		//If this object is active
		bool _isActive = true;

		//A pointer to the parent
		Entity* _parent = nullptr;

		friend Entity;
	};
}