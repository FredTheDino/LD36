#include "inputhandler.h"

using namespace Jam;

std::thread* InputHandler::_ioThread = nullptr;
bool InputHandler::_ioThreadExists = false;
std::unordered_map<InputBinding, std::string> InputHandler::_inputMapper;
std::unordered_map<std::string, InputData> InputHandler::_inputDataList;
std::vector<SDL_Event> InputHandler::_eventQueue;
std::vector<SDL_GameController*> InputHandler::_controllers;
std::vector<short> InputHandler::_controllerRemapper;

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

	_ioThread = new std::thread(&InputHandler::_save);

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
	for (auto it = _inputDataList.begin(); it != _inputDataList.end(); ++it) {
		it->second.status = (KeyState) (it->second.status & (KeyState::DOWN | KeyState::UP));
	}

	std::vector<SDL_Event> workingQueue = _eventQueue;
	_eventQueue.clear();
	
	SDL_Event e;
	InputBinding data;
	for (size_t i = 0; i < workingQueue.size(); i++) {
		e = workingQueue[i];
		switch (e.type) {
			//Input handleing (BEGIN)
			case SDL_KEYDOWN:
			{
				if (e.key.repeat == 0) {
					data = InputBinding(true, -1, e.key.keysym.mod & (KMOD_SHIFT | KMOD_CTRL | KMOD_ALT), e.key.keysym.sym);
					keyEvent(true, data);
				}
				break;
			}
			case SDL_KEYUP:
			{
				if (e.key.repeat == 0) {
					data = InputBinding(true, -1, e.key.keysym.mod & (KMOD_SHIFT | KMOD_CTRL | KMOD_ALT), e.key.keysym.sym);
					keyEvent(false, data);
				}
				break;
			}
			case SDL_CONTROLLERBUTTONDOWN:
			{
				data = InputBinding(false, e.cbutton.which, 0, e.cbutton.button);
				buttonEvent(true, data);
				break;
			}
			case SDL_CONTROLLERBUTTONUP:
			{
				data = InputBinding(false, e.cbutton.which, 0, e.cbutton.button);
				buttonEvent(false, data);
				break;
			}
			case SDL_CONTROLLERAXISMOTION:
			{
				InputBinding input(false, e.caxis.which, 0, e.caxis.axis);
				double axis = (e.caxis.value) / 32768.0;
				axisEvent(axis, input);
				break;
			}
			case SDL_CONTROLLERDEVICEADDED:
			{
				std::cout << "Device added." << std::endl;
				controllerConnectionEvent(true, e.cdevice.which);
				break;
			}
			case SDL_CONTROLLERDEVICEREMOVED:
			{
				std::cout << "Device removed." << std::endl;
				controllerConnectionEvent(false, e.cdevice.which);
				break;
			}
			//Input handleing (END)

			default:
			{
				std::cout << "Type: " << e.type << std::endl;
				break;
			}
		}
	}
}

void Jam::InputHandler::pushEventToQueue(SDL_Event e) {
	_eventQueue.push_back(e);
}

bool Jam::InputHandler::registerInput(const std::string& name, InputBinding binding) {
	if (_find(name) != nullptr) {
		InputData data;
		_inputDataList.insert(std::make_pair(name, data));
	}

	_inputMapper.insert(std::make_pair(binding, name));
	return true;
}

bool Jam::InputHandler::checkInputState(const std::string& name, KeyState keyState) {
	return (_find(name)->status & keyState) != 0;
}

void Jam::InputHandler::keyEvent(bool wasPressed, InputBinding & binding) {
	
	for (auto it = _inputMapper.begin(); it != _inputMapper.end(); it++) {
		if (binding == it->first) {
			if (wasPressed) {
				_inputDataList[it->second].status = (KeyState) KeyState::DOWN | KeyState::PRESSED;
			} else {
				_inputDataList[it->second].status = (KeyState) KeyState::UP | KeyState::RELEASED;
			}
		}
	}
}

void Jam::InputHandler::buttonEvent(bool wasPressed, InputBinding & binding) {
	std::cout << "TODO: InputHandler::buttonEvent" << std::endl;
	
	//Translate the controller to be something more manigable
	for (size_t i = 0; i < _controllerRemapper.size(); i++) {
		if (_controllerRemapper[i] == binding.dev) {
			binding.dev = (int) i;
			break;
		}
	}

	for (auto it = _inputMapper.begin(); it != _inputMapper.end(); it++) {
		if (binding == it->first) {
			if (wasPressed) {
				_inputDataList[it->second].status = (KeyState) KeyState::DOWN | KeyState::PRESSED;
			} else {
				_inputDataList[it->second].status = (KeyState) KeyState::UP | KeyState::RELEASED;
			}
		}
	}
}

void Jam::InputHandler::axisEvent(double value, InputBinding & data) {
	std::cout << "TODO: InputHandler::axisEvent" << std::endl;
}

void Jam::InputHandler::controllerConnectionEvent(bool connect, int which) {
	if (connect) {
		_controllers.push_back(SDL_GameControllerOpen(which));
		printf("Controller connected\n");
		printf("SDL_Init failed: %s\n", SDL_GetError());

		//Check for an opening
		for (size_t i = 0; i < _controllerRemapper.size(); i++) {
			if (_controllerRemapper[i] == -1) {
				_controllerRemapper[i] = which;
				return;
			}
		}

		//Else just add it
		_controllerRemapper.push_back(which);

	} else {

		printf("Controller disconnected\n");
		SDL_GameControllerClose(_controllers[which]);

		for (size_t i = 0; i < _controllerRemapper.size(); i++) {
			if (_controllerRemapper[i] == which) {
				_controllerRemapper[i] = -1;
				return;
			}
		}

	}
}

InputData* Jam::InputHandler::_find(const std::string& name) {
	return &_inputDataList[name];
}

InputData * Jam::InputHandler::_find(InputBinding& binding) {
	for (auto it = _inputMapper.begin(); it != _inputMapper.end(); ++it) {
		if (binding == it->first)
			return &_inputDataList[it->second];
	}

	return nullptr;
}

void Jam::InputHandler::_load() {
	std::cout << "TODO: InputHandler::_load" << std::endl;
}

void Jam::InputHandler::_save() {
	std::cout << "TODO: Inputhandler::_save" << std::endl;
}
