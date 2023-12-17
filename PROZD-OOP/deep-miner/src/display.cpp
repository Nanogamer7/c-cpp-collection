#include "display.h"
#include "bot.h"

void display::topLayer(world *game_world)
{
	using namespace std;

	auto surface = game_world->getSurfaceLayer();
	auto top = game_world->getTopLayer();
	cout << "Current top layer:" << endl;
	cout << "   |   ";
	for (int x = 0; x < WORLD_SIZE_X; x++) {
		cout << setw(2) << x+1 << "    ";
	}
	cout << endl << "---+-" << string(WORLD_SIZE_X * 6, '-') << endl;
	for (int y = 0; y < WORLD_SIZE_Y; y++) {
		cout << " " << (char) ('A' + y) << " |   ";

		for (int x = 0; x < WORLD_SIZE_X; x++) {
			if(surface[x][y] != nullptr) {
				cout << surface[x][y]->getName() << "   ";
				continue;
			}

			cout << setw(2) << (top[x][y] == 10 ? "X" : to_string(top[x][y])) << "    ";
		}

		cout << endl << "   |" << endl;
	}
}

void display::selection(std::vector<std::string> options)
{
	using namespace std;

	cout << "Select one of the following:" << endl;
	int num = 0;
	for ( auto& opt : options ) {
		num++;
		cout << " [" << num << "]: " << opt << endl;
	}

}

void display::mainMenu()
{
	selection( { "PvE", "EvE", "Quit" } );
}

void display::botSelector()
{
	selection( { "Deep", "Pump", "Filter" } );
}

void display::botStats(bot *bot)
{
	using namespace std;

	cout << "+" << string(50, '-') << "+" << endl;
	cout << " " << bot->strName() << endl;
	cout << "   Score: " << bot->strScore() << endl;
	cout << "   Fuel: " << bot->strFuel() << endl;
	cout << "+" << string(50, '-') << "+" << endl;
	
}