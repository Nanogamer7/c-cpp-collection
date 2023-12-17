#include "world.h"
#include <iomanip>

namespace display {
	void topLayer(world* game_world);
	void selection(std::vector<std::string> options);

	void mainMenu();
	void botSelector();
	void botStats(bot* bot);
}