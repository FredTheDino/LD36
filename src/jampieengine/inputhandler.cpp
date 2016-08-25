#include "inputhandler.h"

#include "loader.h"

using namespace Jam;

Flavor* InputHandler::_flavor = nullptr;
std::thread* InputHandler::_ioThread = nullptr;
bool InputHandler::_ioThreadExists = false;
std::unordered_map<InputBinding, std::string> InputHandler::_inputMapper;
bool InputHandler::_accessingInputMap = false;
std::unordered_map<std::string, InputData> InputHandler::_inputDataList;
MousePos InputHandler::_mouse;
bool InputHandler::_hideMouse = false;
bool InputHandler::_centerMouse = false;
bool InputHandler::_accessingMouse = false;
std::vector<SDL_GameController*> InputHandler::_controllers;
std::vector<short> InputHandler::_controllerRemapper;
bool InputHandler::_accessingControllers = false;

void InputHandler::_init(Flavor& flavor) {
	_ioThreadExists = true;
	_flavor = &flavor;
	_ioThread = new std::thread(&InputHandler::_load);
}

void Jam::InputHandler::_destroy() {
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

void Jam::InputHandler::_update() {
	for (auto it = _inputDataList.begin(); it != _inputDataList.end(); ++it) {
		it->second.status = (KeyState) (it->second.status & (KeyState::DOWN | KeyState::UP));
	}

	std::vector<SDL_Event> workingQueue;
	InputEventQueue::copyEventQueue(&workingQueue);

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
					digitalEvent(true, data);
				}
				break;
			}
			case SDL_KEYUP:
			{
				if (e.key.repeat == 0) {
					data = InputBinding(true, -1, e.key.keysym.mod & (KMOD_SHIFT | KMOD_CTRL | KMOD_ALT), e.key.keysym.sym);
					digitalEvent(false, data);
				}
				break;
			}
			case SDL_CONTROLLERBUTTONDOWN:
			{
				data = InputBinding(false, e.cbutton.which, 0, e.cbutton.button);
				digitalEvent(true, data);
				break;
			}
			case SDL_CONTROLLERBUTTONUP:
			{
				data = InputBinding(false, e.cbutton.which, 0, e.cbutton.button);
				digitalEvent(false, data);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				data = InputBinding(e.button.button); 
				digitalEvent(true, data);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				data = InputBinding(e.button.button);
				digitalEvent(false, data);
				break;
			}
			case SDL_CONTROLLERAXISMOTION:
			{
				InputBinding input(e.caxis.which, e.caxis.axis);
				double axis = (e.caxis.value) / 32768.0;
				axisEvent(axis, input);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				while (_accessingMouse) {}
				_accessingMouse = true;
				
				_mouse.position.x = (float) e.motion.x;
				_mouse.position.y = (float) e.motion.y;
				
				_mouse.delta.x = (float) e.motion.xrel;
				_mouse.delta.y = (float) e.motion.yrel;
				
				_accessingMouse = false;
			}
			//Input handleing (END)

			default:
			{
				e.type;
				break;
			}
		}
	}
}

bool Jam::InputHandler::registerInput(const std::string& name, InputBinding binding) {
	if (_find(name) != nullptr) {
		InputData data;
		_inputDataList.insert(std::make_pair(name, data));
	}
	while (_accessingInputMap) {}
	_accessingInputMap = true;
	_inputMapper.insert(std::make_pair(binding, name));
	_accessingInputMap = false;
	return true;
}

bool Jam::InputHandler::checkInputState(const std::string& name, KeyState keyState) {
	return (_find(name)->status & keyState) != 0;
}

double Jam::InputHandler::getAxisData(const std::string & name) {
	return _find(name)->axis;
}

InputData Jam::InputHandler::getInputData(const std::string & name) {
	return *_find(name);
}

glm::vec2 Jam::InputHandler::getMouseDelta() {
	glm::vec2 out;
	while (_accessingMouse) {}
	_accessingMouse = true;
	out = _mouse.delta;
	_accessingMouse = false;

	return out;
}

glm::vec2 Jam::InputHandler::getMousePos() {
	glm::vec2 out;
	while (_accessingMouse) {}
	_accessingMouse = true;
	out = _mouse.position;
	_accessingMouse = false;

	return out;
}

bool Jam::InputHandler::keyDown(const std::string & name) {
	return checkInputState(name, KeyState::DOWN);
}

bool Jam::InputHandler::keyUp(const std::string & name) {
	return checkInputState(name, KeyState::UP);
}

bool Jam::InputHandler::keyPressed(const std::string & name) {
	return checkInputState(name, KeyState::PRESSED);
}

bool Jam::InputHandler::keyReleased(const std::string & name) {
	return checkInputState(name, KeyState::RELEASED);
}

void Jam::InputHandler::digitalEvent(bool wasPressed, InputBinding & binding) {
	if (binding.dev != -1) {
		for (size_t i = 0; i < _controllerRemapper.size(); i++) {
			if (_controllerRemapper[i] == binding.dev) {
				binding.dev = (int) i;
				break;
			}
		}
	}
	
	while (_accessingInputMap) {}
	_accessingInputMap = true;
	for (auto it = _inputMapper.begin(); it != _inputMapper.end(); it++) {
		if (binding == it->first) {
			if (wasPressed) {
				_inputDataList[it->second].status = (KeyState) KeyState::DOWN | KeyState::PRESSED;
			} else {
				_inputDataList[it->second].status = (KeyState) KeyState::UP | KeyState::RELEASED;
			}
		}
	}
	_accessingInputMap = false;
}

void Jam::InputHandler::axisEvent(double value, InputBinding & binding) {
	//Translate the controller to be something more manigable
	for (size_t i = 0; i < _controllerRemapper.size(); i++) {
		if (_controllerRemapper[i] == binding.dev) {
			binding.dev = (int) i;
			break;
		}
	}

	while (_accessingInputMap) {}
	_accessingInputMap = true;
	for (auto it = _inputMapper.begin(); it != _inputMapper.end(); it++) {
		if (binding == it->first) {
			_inputDataList[it->second].axis = value;
		}
	}
	_accessingInputMap = false;
}

void Jam::InputHandler::controllerConnectionEvent(bool connect, int which) {
	_accessingControllers = true;
	if (connect) {
		_controllers.push_back(SDL_GameControllerOpen(which));

		//Check for an opening
		for (size_t i = 0; i < _controllerRemapper.size(); i++) {
			if (_controllerRemapper[i] == -1) {
				_controllerRemapper[i] = which;
				
				_accessingControllers = false;
				return;
			}
		}

		//Else just add it
		_controllerRemapper.push_back(which);

	} else {
		SDL_GameControllerClose(_controllers[which]);

		for (size_t i = 0; i < _controllerRemapper.size(); i++) {
			if (_controllerRemapper[i] == which) {
				_controllerRemapper[i] = -1;

				_accessingControllers = false;
				return;
			}
		}
	}
}

InputData* Jam::InputHandler::_find(const std::string& name) {
	return &_inputDataList[name];
}

InputData * Jam::InputHandler::_find(InputBinding& binding) {
	while (_accessingInputMap) {}
	_accessingInputMap = true;
	for (auto it = _inputMapper.begin(); it != _inputMapper.end(); ++it) {
		if (binding == it->first)
			return &_inputDataList[it->second];
	}
	_accessingInputMap = false;

	return nullptr;
}

void Jam::InputHandler::_load() {
	
	std::fstream* file = Loader::openFile(_flavor->inputmap);
	std::string name;
	std::string line;
	
	while (getline(*file, line))
	{
		// All lines begining with # are comments
		if (line[0] == '#') continue;
		InputBinding binding(&name, line);
		registerInput(name, binding);
	}
	
	file->close();
	delete file;
}

void Jam::InputHandler::_save() {
	std::fstream* file = Loader::openFile(_flavor->inputmap);
	std::string name;
	std::string line;
	std::vector<std::string> comments;

	// All lines begining with # are comments, add them to a list and push back
	while (getline(*file, line)) {
		if (line[0] == '#') {
			comments.push_back(line + "\n");
		}
	}

	file->close();
	delete file;

	//Create a copy 
	while (_accessingInputMap) {}
	_accessingInputMap = true;
	std::unordered_map<InputBinding, std::string> inputMapperCopy = _inputMapper;
	_accessingInputMap = false;

	file = Loader::openFile(_flavor->inputmap, std::ios_base::out | std::ios_base::trunc);

	//Write comments
	for (size_t i = 0; i < comments.size(); i++) {
		file->write(comments[i].c_str(), comments[i].size());
	}

	//Write data
	for (auto it = inputMapperCopy.begin(); it != inputMapperCopy.end(); it++) {
		std::string out = it->second + it->first.toString();
		file->write(out.c_str(), out.size());
	}

	file->close();
	delete file;
}