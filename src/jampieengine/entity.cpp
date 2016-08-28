#include "entity.h"
#include "entity.h"
#include "entity.h"
#include "renderer.h"
#include "box2dcomponent.h"

using namespace Jam;

Entity::Entity() {}

Entity::~Entity()
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_end();
	}

	for (size_t i = 0; i < _components.size(); i++) {
		delete _components[i];
	}
	_components.clear();
}

void Entity::setAll(bool active)
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->setActive(active);
	}
}

void Entity::toggleAll() {
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->toggleActive();
	}
}

void Jam::Entity::move(float x, float y, float z) {
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Transform t = c->body->GetTransform();
		t.p.x += x;
		t.p.y += y;
		c->body->SetTransform(t.p, t.q.GetAngle());

		transform.position.x = t.p.x;
		transform.position.y = t.p.y;
		transform.position.z += z;
	} else {
		transform.position.x += x;
		transform.position.y += y;
		transform.position.z += z;
	}
}

void Jam::Entity::move(glm::vec3 dpos) {
	move(dpos.x, dpos.y, dpos.z);
}

void Jam::Entity::setPosition(glm::vec3 newPos) {
	transform.position = newPos;
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		float32 angle = c->body->GetTransform().q.GetAngle();
		c->body->SetTransform(b2Vec2(newPos.x, newPos.y), angle);
	}
}

glm::vec3 Jam::Entity::getPosition() {
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Vec2 v = c->body->GetTransform().p;
		return glm::vec3(v.x, v.y, transform.position.z);
	} else {
		return transform.position;
	}
}

void Jam::Entity::scale(float scalar) {
	transform.scale.x *= scalar;
	transform.scale.y *= scalar;
	transform.scale.z *= scalar;
}

void Jam::Entity::scale(float x, float y, float z) {
	transform.scale.x *= x;
	transform.scale.y *= y;
	transform.scale.z *= z;
}

void Jam::Entity::setScale(glm::vec3 scale) {
	transform.scale = scale;
}

glm::vec3 Jam::Entity::getScale() {
	return transform.scale;
}

void Jam::Entity::rotate(float z) {
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Transform t = c->body->GetTransform();
		c->body->SetTransform(t.p, t.q.GetAngle() + z);
		transform.rotation.z = t.q.GetAngle() + z;
	} else {
		transform.rotateZ(z);
	}
}

void Jam::Entity::rotate(float x, float y, float z) {
	transform.rotate(x, y, z);

	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Transform t = c->body->GetTransform();
		c->body->SetTransform(t.p, t.q.GetAngle() + z);
		transform.rotation.z = t.q.GetAngle() + z;
	}
}

void Jam::Entity::setRotation(glm::vec3 newRotation) {
	transform.rotation = newRotation;
	
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Transform t = c->body->GetTransform();
		c->body->SetTransform(t.p, newRotation.z);
	}
}

glm::vec3 Jam::Entity::getRotation() {
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		return transform.rotation;
	} else {
		return glm::vec3(
			transform.rotation.x,
			transform.rotation.y,
			c->body->GetAngle()
			);
	}
}

glm::mat4 Jam::Entity::getTransformationMatrix() {
	return transform.getMatrix();
}

Transform Jam::Entity::getTransform() {
	return transform;
}

void Entity::update(double delta)
{
	if (has<Renderer>())
		while (get<Renderer>()->shouldDraw());

	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_update(delta);
	}
	if (has<Renderer>())
		get<Renderer>()->setShouldDraw(true);

}

void Entity::_rootEnter()
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_rootEnter();
	}
}

void Entity::_rootExit()
{
	for (size_t i = 0; i < _components.size(); i++) {
		_components[i]->_rootExit();
	}
}