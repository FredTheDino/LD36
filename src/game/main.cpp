#include "pie.h"

#include "loader.h"

int main(int c, char** args) {

	Jam::Loader::prefix = "../../res/";

	std::cout << Jam::Loader::loadText("test.txt") << std::endl;

	Jam::Flavor flavor;
	flavor.title = "My Test Game";

	Jam::InputHandler::registerInput(Jam::InputData("test", true, -1, 0, 97 /* a */));

	Jam::Pie pie(flavor);

	pie.bake();

	return 0;
}