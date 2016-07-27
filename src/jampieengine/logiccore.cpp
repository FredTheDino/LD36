#include "logiccore.h"
#include "pie.h"

using namespace Jam;

LogicCore::LogicCore(Pie& pie, Flavor& flavor)
	: _pie(pie)
{
	InputHandler::init();
}

void LogicCore::_bake(Flavor& flavor)
{
	_thread = new std::thread(&LogicCore::_start, this);
}

void LogicCore::_start()
{
	while (_pie.isCooking()) {
		InputHandler::update();

		if (InputHandler::checkInputState("test", KeyState::RELEASED)) {
			std::cout << "WOOT!" << std::endl;
		}
	}
}

LogicCore::~LogicCore()
{
	_thread->join();
	delete _thread;
	InputHandler::destroy();
}