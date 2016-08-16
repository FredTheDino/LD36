#include "root.h"

using namespace Jam;

Root::Root(GameState& gameState)
	: _gameState(gameState)
{

}

void Root::update(double delta)
{
	for (std::pair<int, std::string> ref : _priorities) {
		_nodes.at(ref.second)->update(delta);
	}
}

Root::~Root()
{

}