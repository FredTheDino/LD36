#pragma once

#include "component.h"

class IntComponent : public Jam::Component
{
public:
	IntComponent(int i = 0) { _val = i; };

	void _rootEnter() {};
	void _init() {};
	void _update(double delta) {};
	void _end() {};
	void _rootExit() {};

	void set(int i) { _val = i; };
	int get() { return _val; };

private:
	int _val;
};