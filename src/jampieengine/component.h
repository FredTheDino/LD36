#pragma once

namespace {
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

		void setParent(Entity& parent);

		virtual void update() {};

	protected:

		Component(ComponentTypes type);

		ComponentTypes _type = COMPONENT;
		Entity* _parent;

		friend Entity;
	};
}