#include "shop.h"

#include "level.h"

using namespace Jam;

const unsigned int Shop::ITEM_COUNT = 3;
const unsigned int Shop::COINS_PER_BAR = 8;

bool Shop::mayPlace = true;

Item Shop::selectedItem = ITEM_ROOM;

Entity* Shop::previousButton = nullptr;

Shop::Shop(Level* level, int currency)
	: _level(level), _currency(currency)
{

	int bars = ceil(((float)currency) / COINS_PER_BAR);
	_coinBars.resize(bars);

	for (unsigned int i = 0; i < bars; i++) {
		_coinBars[i] = new Entity();
		_coinBars[i]->add(new GUIFader(_level->_renderEngine, 100, 1, 1, "coins_on", "coins_off", "coins_map"));
		_coinBars[i]->scale(140, 22);
		_coinBars[i]->transform.translate((float)-92, ((float)-22) * i - 32);

		_level->_root->addNode(0, std::to_string(i) + "_cb", (Node*) _coinBars[i]);
	}

	_updateCoinBars();
}

void Shop::_init()
{
	//Load textures
	for (unsigned int i = 0; i < ITEM_COUNT; i++) {
		RenderEngine::preloadTexture(std::to_string(i) + "_on");
		RenderEngine::preloadTexture(std::to_string(i) + "_off");
	}

	RenderEngine::load();

	while (RenderEngine::remainingLoadEntries() > 0);

	//Generate entities
	for (unsigned int i = 0; i < ITEM_COUNT; i++) {
		Entity* button = new Entity();
		b2CircleShape shape;
		shape.m_radius = 32;
		button->add(new GUIButton(_level->_renderEngine, 100, -1, -1, std::to_string(i) + (selectedItem == i ? "_on" : "_off"), &shape));
		button->get<GUIButton>()->setOnHighlight(callback_item_highlight);
		button->get<GUIButton>()->setOnDehighlight(callback_item_dehighlight);
		button->get<GUIButton>()->setOnPress(callback_item_click);
		button->scale(64);
		button->transform.translate((i + 1) * 64, 64);

		button->add(new IntComponent(i));

		_level->_root->addNode(0, "item_" + std::to_string(i), (Node*) button);

		if (i == selectedItem)
			previousButton = button;
	}
}

void Shop::_update(double delta)
{
	if (InputHandler::keyPressed("ui_select")) {
		
		glm::vec2 pos = Level::toGLSpace(_level->_renderEngine, InputHandler::getMousePos());

		if (pos.x < Terrain::CHUNK_SIZE || pos.x >(_level->_chunksX - 1) * Terrain::CHUNK_SIZE ||
			-pos.y < Terrain::CHUNK_SIZE || -pos.y > (_level->_chunksY - 1) * Terrain::CHUNK_SIZE || !mayPlace) {
			return;
		}

		int x = floor(pos.x / Terrain::CHUNK_SIZE);
		int y = floor((-pos.y) / Terrain::CHUNK_SIZE);
		Chunk c = ((Entity*)_level->_root->getNode("terrain"))->get<Terrain>()->getChunk(x, y);

		switch (selectedItem) {
		case ITEM_ROOM:
			if (c.type == CHUNK_TYPE_SOLID) {
				if (!_buy())
					break;
				_level->buyChunk(x, y);
			}
			else if (c.type == CHUNK_TYPE_NORMAL) {
				if (!_sell())
					break;
				_level->sellChunk(x, y);
			}
			break;
		case ITEM_SPIKE:
		case ITEM_ARROW:
		case ITEM_FIRE:
			int tx = floor(pos.x);
			int ty = -floor(pos.y) - 1;
			
			std::cout << _level->getTile(tx, ty).tileType << std::endl;

			if (_level->getTrap(tx, ty).x == -1) {
				if (_level->getTile(tx, ty + 1).tileType != TILE_TYPE_SOLID || _level->getTile(tx, ty).tileType == TILE_TYPE_SOLID)
					break;

				if (!_buy())
					break;
				_level->buyTrap(selectedItem, tx, ty);
			}
			else if (_level->getTrap(tx, ty).trapType == TrapType(selectedItem - 1)) {
				if (!_sell())
					break;
				_level->sellTrap(selectedItem, tx, ty);
			}
			_updateCoinBars();
			break;
		}
	}
}

bool Shop::_buy()
{
	if (_currency == 0)
		return false;

	_currency--;

	_updateCoinBars();

	return true;
}

bool Shop::_sell()
{
	_currency++;

	_updateCoinBars();

	return true;
}

void Shop::_updateCoinBars()
{
	int bar = floor(((float)(abs(_currency - 1))) / COINS_PER_BAR);

	for (int i = 0; i <= bar && i < _coinBars.size(); i++) {
		_coinBars[i]->get<GUIFader>()->setValue(0.0f);
	}

	/*if (bar == _coinBars.size())
		bar;*/

	_coinBars[bar]->get<GUIFader>()->setValue((248.0f - ((float)(_currency % COINS_PER_BAR)) * 31.0f) / 255.0f);

	/*for (int i = bar + 1; i < _coinBars.size(); i++) {
		_coinBars[i]->get<GUIFader>()->setValue(1.0f);
	}*/

}

void callback_item_highlight(GUIInput* component)
{
	Shop::mayPlace = false;
}

void callback_item_dehighlight(GUIInput* component)
{
	Shop::mayPlace = true;
}

void callback_item_click(Jam::GUIInput* component)
{
	if (Shop::previousButton != nullptr)
		Shop::previousButton->get<GUIButton>()->setTexture(std::to_string(Shop::previousButton->get<IntComponent>()->get()) + "_off");
	
	int i = component->getParent()->get<IntComponent>()->get();

	component->setTexture(std::to_string(i) + "_on");

	Shop::selectedItem = (Item) i;

	Shop::previousButton = component->getParent();
}