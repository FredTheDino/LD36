#pragma once

#include "gamestate.h"
#include "guibutton.h"

class MenuState : Jam::GameState
{
public:

	void init();
	void update(double deta);
	void exit();


private:

	void _loadContent();

	void _initMainMenu();

	/* Callbacks */
};

void callback_button_highlight(Jam::GUIInput* component);
void callback_button_dehighlight(Jam::GUIInput* component);