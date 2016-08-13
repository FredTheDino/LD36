#include "logiccore.h"

#include "pie.h"

using namespace Jam;

LogicCore::LogicCore(Pie& pie, Flavor& flavor)
	: Core(pie)
{
	InputHandler::init();
}

void LogicCore::_bake(Flavor& flavor)
{
	_thread = new std::thread(&LogicCore::_start, this);
}

void LogicCore::_start()
{
	Jam::Time::setFPS(60);
	Time::registerThread();

	static unsigned fps = 30;

	while (_pie.isCooking()) {
		InputHandler::update();
		if (InputHandler::checkInputState("fpsUP", KeyState::PRESSED)) {
			fps += 30;
			Time::setFPS(fps);
			printf("New FPS target: %i\n", fps);
		}
		if (InputHandler::checkInputState("fpsDOWN", KeyState::PRESSED)) {
			fps -= 30;
			Time::setFPS(fps);
			printf("New FPS target: %i\n", fps);
		}
		Time::wait();
	}
	Time::unregisterThread();
}

LogicCore::~LogicCore()
{
	_thread->join();
	delete _thread;
	InputHandler::destroy();
}