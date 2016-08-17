#include "pie.h"

#include <SDL2/SDL.h>
#include "loader.h"

#include "gamestate.h"
#include "gamestatelibrary.h"
#include "root.h"
#include "entity.h"
#include "node.h"
#include "component.h"

class TestComponent : public Jam::Component
{
public:
	void _begin()
	{
		std::cout << "test!!!!!!!!!!!!!" << std::endl;
	}

	void _update(double delta)
	{
		if (Jam::InputHandler::checkInputState("t_increment", Jam::KeyState::PRESSED))
			i++;

		if (Jam::InputHandler::checkInputState("t_decrement", Jam::KeyState::PRESSED))
			i--;
		
		std::cout << i << std::endl;
	}

	void _end()
	{

	}

	void reset()
	{
		i = 0;
	}

private:
	int i;
};

class TestState : Jam::GameState
{
public:
	void init()
	{
		std::cout << "Test1: Adding roots..." << std::endl;

		root = new Jam::Root(*this);

		Jam::Entity* entity = new Jam::Entity();

		entity->add(new TestComponent());

		root->addNode(1, "TestEntity", (Jam::Node*) entity);
		addRoot("TestRoot", root);
		
		enterRoot("TestRoot");
	}

	void update(double delta)
	{
		if(Jam::InputHandler::checkInputState("t_reset", Jam::KeyState::PRESSED))
			((Jam::Entity*) getCurrentRoot()->getNode("TestEntity"))->get<TestComponent>()->reset();
	}

	void exit()
	{
		removeRoot("TestRoot");
		delete root;
	}

private:
	Jam::Root* root = nullptr;
};

int main(int c, char** args) {
	Jam::GameStateLibrary::registerGameState("TestState", (Jam::GameState*) new TestState());

	Jam::InputHandler::registerInput("t_increment", Jam::InputBinding(true, -1, 0, SDLK_o));
	Jam::InputHandler::registerInput("t_decrement", Jam::InputBinding(true, -1, 0, SDLK_i));
	Jam::InputHandler::registerInput("t_reset", Jam::InputBinding(true, -1, 0, SDLK_p));

	Jam::Time::setFPS(60);

	//Jam::Loader::prefix = "../res/";
	Jam::Loader::prefix = "../../res/";

	std::cout << Jam::Loader::loadText("test.txt") << std::endl;
	
	Jam::Flavor flavor;
	
	flavor.title = "My Test Game";
	flavor.enterState = "TestState";

	Jam::Pie pie(flavor);

	pie.bake();

	return 0;
}