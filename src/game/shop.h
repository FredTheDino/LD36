#pragma once

#include "level.h"

#include "guibutton.h"

#include "intcomponent.h"

#include "entity.h"

class Level;

enum Item {
	ITEM_ROOM,
	ITEM_SPIKE
};

class Shop : public Jam::Component
{
public:
	Shop(Level* level);

	void _rootEnter() {};
	void _init();
	void _update(double delta);
	void _end() {};
	void _rootExit() {};

	static const unsigned int ITEM_COUNT;

	static bool mayPlace;

	static Item selectedItem;

	static Jam::Entity* previousButton;

private:

	Level* _level;

};
	/* Callbacks */

	void callback_item_highlight(Jam::GUIInput* component);
	void callback_item_dehighlight(Jam::GUIInput* component);
	void callback_item_click(Jam::GUIInput* component);