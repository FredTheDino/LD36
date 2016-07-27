#include "inputhandler.h"

using namespace Jam;

std::thread* InputHandler::_ioThread = nullptr;
bool InputHandler::_ioThreadExists = false;
std::unordered_map<std::string, InputData> InputHandler::_inputList;

void InputHandler::init() {
	_ioThread = new std::thread(&InputHandler::_load);
	_ioThreadExists = true;
}

void Jam::InputHandler::destroy() {
	while (true) {
		if (ready()) {
			break;
		}
	}
}

bool InputHandler::ready() {
	if (_ioThreadExists) {
		if (_ioThread->joinable()) {
			_ioThread->join();
			delete _ioThread;
			_ioThreadExists = false;
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

void Jam::InputHandler::update() {
	std::cout << "Hello world!" << std::endl;
	for (auto it = _inputList.begin(); it != _inputList.end(); ++it) {
		it->second.status = (KeyState) (it->second.status & KeyState::DOWN);
	}
}

bool Jam::InputHandler::registerInput(InputData data) {
	if (_find(data.name) == nullptr) {
		std::cout << "Input allocation error: \"" << data.name << "\" allready taken." << std::endl;
		return false;
	}

	_inputList.insert(std::make_pair(data.name, data));
	return true;
}

bool Jam::InputHandler::checkInputState(const std::string& name, KeyState keyState) {
	return (_find(name)->status & keyState) != 0;
}

bool Jam::InputHandler::keyEvent(bool wasPressed, InputData & data) {
	std::cout << "TODO: InputHandler::keyEvent" << std::endl;
	return false;
}

bool Jam::InputHandler::buttonEvent(bool wasPressed, InputData & data) {
	std::cout << "TODO: InputHandler::buttonEvent" << std::endl;
	return false;
}

bool Jam::InputHandler::axisEvent(InputData & data) {
	std::cout << "TODO: InputHandler::axisEvent" << std::endl;
	return false;
}

InputData* Jam::InputHandler::_find(const std::string& name) {
	//I could also write std::unordered_map<const std::string&,InputData*>::const_iterator
	auto it = _inputList.find(name);

	if (it == _inputList.end())
		return nullptr;
	
	return &it->second;
}

InputData * Jam::InputHandler::_find(InputData& data) {
	for (auto it = _inputList.begin(); it != _inputList.end(); ++it) {
		if (it->second == data)
			return &it->second;
	}

	return nullptr;
}

void Jam::InputHandler::_load() {
	std::cout << "TODO: InputHandler::_load" << std::endl;
}

void Jam::InputHandler::_save() {
	std::cout << "TODO: Inputhandler::_save" << std::endl;
}
