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

		_transform.position.x = t.p.x;
		_transform.position.y = t.p.y;
		_transform.position.z += z;
	} else {
		_transform.position.x += x;
		_transform.position.y += y;
		_transform.position.z += z;
	}
}

void Jam::Entity::move(glm::vec3 dpos) {
	move(dpos.x, dpos.y, dpos.z);
}

void Jam::Entity::setPosition(glm::vec3 newPos) {
	_transform.position = newPos;
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
		return glm::vec3(v.x, v.y, _transform.position.z);
	} else {
		return _transform.position;
	}
}

void Jam::Entity::scale(float scalar) {
	_transform.scale.x *= scalar;
	_transform.scale.y *= scalar;
	_transform.scale.z *= scalar;
}

void Jam::Entity::scale(float x, float y, float z) {
	_transform.scale.x *= x;
	_transform.scale.y *= y;
	_transform.scale.z *= z;
}

void Jam::Entity::setScale(glm::vec3 scale) {
	_transform.scale = scale;
}

glm::vec3 Jam::Entity::getScale() {
	return _transform.scale;
}

void Jam::Entity::rotate(float z) {
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Transform t = c->body->GetTransform();
		c->body->SetTransform(t.p, t.q.GetAngle() + z);
		_transform.rotation.z = t.q.GetAngle() + z;
	} else {
		_transform.rotateZ(z);
	}
}

void Jam::Entity::rotate(float x, float y, float z) {
	_transform.rotate(x, y, z);

	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Transform t = c->body->GetTransform();
		c->body->SetTransform(t.p, t.q.GetAngle() + z);
		_transform.rotation.z = t.q.GetAngle() + z;
	}
}

void Jam::Entity::setRotation(glm::vec3 newRotation) {
	_transform.rotation = newRotation;
	
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		b2Transform t = c->body->GetTransform();
		c->body->SetTransform(t.p, newRotation.z);
	}
}

glm::vec3 Jam::Entity::getRotation() {
	Box2DComponent* c = get<Box2DComponent>();
	if (c) {
		return _transform.rotation;
	} else {
		return glm::vec3(
			_transform.rotation.x,
			_transform.rotation.y,
			c->body->GetAngle()
			);
	}
}

glm::mat4 Jam::Entity::getTransformationMatrix() {
	return _transform.getMatrix();
}

Transform Jam::Entity::getTransform() {
	return _transform;
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