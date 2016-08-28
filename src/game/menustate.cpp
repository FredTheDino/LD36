#include "menustate.h"

#include "trapcomponent.h"

using namespace Jam;

static bool enterState = false;

void MenuState::init()
{
	_loadContent();

	_initMainMenu();

	enterRoot("menu_main");
}

void MenuState::update(double delta)
{

}

void MenuState::exit()
{

}

void MenuState::playGame()
{
	_gameStateManager->enterState("play");
}

/* Initialization */

void MenuState::_initMainMenu()
{
	Root* mainMenu = new Root();

	//Play button
	Entity* playButton = new Entity();
	playButton->scale(128); // 128x128 button

	b2PolygonShape shape;
	shape.SetAsBox(64, 64);

	playButton->add(new GUIButton(getRenderEngine(), 0, 0, .4, "button_play", &shape));
	playButton->get<GUIButton>()->setOnHighlight(callback_button_highlight);
	playButton->get<GUIButton>()->setOnDehighlight(callback_button_dehighlight);
	playButton->get<GUIButton>()->setOnPress(callback_button_play);
	
	mainMenu->addNode(0, "button_play", (Node*) playButton);

	//Exit button
	Entity* exitButton = new Entity();
	exitButton->scale(128); // 128x128 button

	exitButton->add(new GUIButton(getRenderEngine(), 0, 0, -.4, "button_exit", &shape));
	exitButton->get<GUIButton>()->setOnHighlight(callback_button_highlight);
	exitButton->get<GUIButton>()->setOnDehighlight(callback_button_dehighlight);

	mainMenu->addNode(0, "button_exit", (Node*) exitButton);

	//InputHandler::registerInput("ui_select", InputBinding(1));

	//Add root
	addRoot("menu_main", mainMenu);
}

void MenuState::_loadContent()
{
	//Textures
	RenderEngine::preloadTexture("button_play");
	RenderEngine::preloadTexture("button_exit");

	//Load
	RenderEngine::load();

	while (RenderEngine::remainingLoadEntries() > 0);
}

/* Callbacks */

void callback_button_highlight(GUIInput* component)
{
	component->setBaseColor(glm::vec4(.7f, .7f, .7f, 1));
}

void callback_button_dehighlight(GUIInput* component)
{
	component->setBaseColor(glm::vec4(1, 1, 1, 1));
}

void callback_button_play(GUIInput* component)
{
	((MenuState*) GameStateLibrary::getGameState("menu"))->playGame();
}