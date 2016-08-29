#pragma once

#include "guibutton.h"

#include "intcomponent.h"

#include "entity.h"

class Level;

enum Item {
	ITEM_ROOM,
	ITEM_SPIKE,
	ITEM_ARROW,
	ITEM_FIRE
};

class Shop : public Jam::Component
{
public:
	Shop(Level* level, int currency);

	void _rootEnter() {};
	void _init();
	void _update(double delta);
	void _end() {};
	void _rootExit() {};

	static const unsigned int ITEM_COUNT;
	static const unsigned int COINS_PER_BAR;

	static bool mayPlace;

	static Item selectedItem;

	static Jam::Entity* previousButton;

private:

	Level* _level;

	std::vector<Jam::Entity*> _coinBars;

	int _currency;

	bool _buy();
	bool _sell();

	void _updateCoinBars();
};
	/* Callbacks */

	void callback_item_highlight(Jam::GUIInput* component);
	void callback_item_dehighlight(Jam::GUIInput* component);
	void callback_item_click(Jam::GUIInput* component);