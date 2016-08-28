#include "shop.h"

using namespace Jam;

unsigned const int Shop::ITEM_COUNT = 2;

bool Shop::mayPlace = true;

Item Shop::selectedItem = ITEM_ROOM;

Entity* Shop::previousButton = nullptr;

Shop::Shop(Level* level)
	: _level(level)
{

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

		if (pos.x < 0 || pos.x > _level->_chunksX * LevelBackground::CHUNK_SIZE ||
			-pos.y < 0 || -pos.y > _level->_chunksY * LevelBackground::CHUNK_SIZE || !mayPlace) {
			return;
		}
		switch (selectedItem) {
		case ITEM_ROOM:
			_level->buyChunk(floor(pos.x / LevelBackground::CHUNK_SIZE), floor((-pos.y) / LevelBackground::CHUNK_SIZE));
			break;
		}
	}
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