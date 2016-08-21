#pragma once

#include "box2dlistener.h"
#include "Box2D/Box2D.h"
#include "box2dcomponent.h"

namespace Jam {
	
	void Box2DListener::BeginContact(b2Contact* contact) {

			Box2DComponent* component;
			void* userData = contact->GetFixtureA()->GetBody()->GetUserData();
			if (userData) {
				component = static_cast<Box2DComponent*>(userData);
				if (component->_beginContactCallback) {
					component->_beginContactCallback(contact);
				}
			}

			userData = contact->GetFixtureB()->GetBody()->GetUserData();
			if (userData) {
				component = static_cast<Box2DComponent*>(userData);
				if (component->_beginContactCallback) {
					component->_beginContactCallback(contact);
				}
			}
		}

		void Box2DListener::EndContact(b2Contact* contact) {

			Box2DComponent* component;
			void* userData = contact->GetFixtureA()->GetBody()->GetUserData();
			if (userData) {
				component = static_cast<Box2DComponent*>(userData);
				if (component->_beginContactCallback) {
					component->_beginContactCallback(contact);
				}
			}

			userData = contact->GetFixtureB()->GetBody()->GetUserData();
			if (userData) {
				component = static_cast<Box2DComponent*>(userData);
				if (component->_beginContactCallback) {
					component->_beginContactCallback(contact);
				}
			}
		}

	}