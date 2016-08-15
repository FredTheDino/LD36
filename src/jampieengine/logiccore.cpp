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
	Time::registerThread();

	while (_pie.isCooking()) {
		InputHandler::update();
		Time::wait();
	}

	Time::unregisterThread();
}

LogicCore::~LogicCore()
{
	InputHandler::destroy();
}