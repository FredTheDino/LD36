#include "audiolistener.h"

#include "audioeventqueue.h"

float Jam::AudioListener::_gain = 0;

glm::vec3 Jam::AudioListener::_position = glm::vec3();
glm::vec3 Jam::AudioListener::_velocity = glm::vec3();
glm::vec3 Jam::AudioListener::_up = glm::vec3(0.0, 1.0, 0.0);
glm::vec3 Jam::AudioListener::_forward = glm::vec3(0.0, 0.0, 1.0);

glm::vec3 Jam::AudioListener::getPosition() {
	return _position;
}

glm::vec3 Jam::AudioListener::getVelocity() {
	return _velocity;
}

glm::vec3 Jam::AudioListener::getUp() {
	return _up;
}

glm::vec3 Jam::AudioListener::getForward() {
	return _forward;
}

float Jam::AudioListener::getGain() {
	return _gain;
}

void Jam::AudioListener::setMasterVolume(float gain) {
	_gain = gain;
	AudioEvent ae;

	ae.type = AudioEventData::Type::LISTENER;
	ae.target = AL_GAIN;
	ae.fData[0] = gain;

	AudioEventQueue::pushDataToQueue(ae);
}

void Jam::AudioListener::setPosition(float x, float y, float z) {
	setPosition(glm::vec3(x, y, z));
}

void Jam::AudioListener::setPosition(glm::vec3 pos) {
	_position = pos;
	AudioEvent ae;

	ae.type = AudioEventData::Type::LISTENER;
	ae.target = AL_POSITION;

	for (size_t i = 0; i < 3; i++) {
		ae.fData[i] = pos[i];
	}

	AudioEventQueue::pushDataToQueue(ae);
}

void Jam::AudioListener::setVelocity(float x, float y, float z) {
	setVelocity(glm::vec3(x, y, z));
}

void Jam::AudioListener::setVelocity(glm::vec3 vel) {
	_velocity = vel;
	AudioEvent ae;

	ae.type = AudioEventData::Type::LISTENER;
	ae.target = AL_VELOCITY;

	for (size_t i = 0; i < 3; i++) {
		ae.fData[i] = vel[i];
	}

	AudioEventQueue::pushDataToQueue(ae);
}

void Jam::AudioListener::setOrientation(float x1, float y1, float z1, float x2, float y2, float z2) {
	setOrientation(glm::vec3(x1, y1, z1), glm::vec3(x2, y2, z2));
}

void Jam::AudioListener::setOrientation(glm::vec3 forward, glm::vec3 up) {
	_forward = forward;
	_up = up;

	AudioEvent ae;

	ae.type = AudioEventData::Type::LISTENER;
	ae.target = AL_ORIENTATION;

	for (size_t i = 0; i < 3; i++) {
		ae.fData[i] = forward[i];
	}

	for (size_t i = 0; i < 3; i++) {
		ae.fData[2 + i] = up[i];
	}

	AudioEventQueue::pushDataToQueue(ae);
}
