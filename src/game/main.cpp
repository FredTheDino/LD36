#include "pie.h"

int main(int c, char** args) {

	Jam::Flavor flavor;
	flavor.title = "My Test Game";

	Jam::InputHandler::registerInput("test", Jam::InputBinding(true, -1, 0, 97 /* a */));

	Jam::Pie pie(flavor);

	pie.bake();


	return 0;
}