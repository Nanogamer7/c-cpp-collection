#include "game.h"
#include "bot.h"
#include "display.h"
#include <ctime>

game::game() {}

game::~game() {
	for (auto& bot : this->bots) {
		delete bot;
	}
}

void game::startGame() 
{
	this->game_world = new world();
	this->game_world->fillWorld(time(NULL));
	std::vector<int> coords(WORLD_SIZE_X * WORLD_SIZE_Y);
    std::iota(coords.begin(), coords.end(), 0);
    std::shuffle(coords.begin(), coords.end(), std::default_random_engine{}); // TODO: not random?
	for ( auto& bot : bots ) {
		bot->setWorld(this->game_world);
		bot->setCoords( { coords.at(0) / WORLD_SIZE_X, coords.at(0) % WORLD_SIZE_Y } );
		this->game_world->addBot(bot, { coords.at(0) / WORLD_SIZE_X, coords.at(0) % WORLD_SIZE_Y } );
		coords.erase(coords.begin());
	}
	this->playing = this->bots;

	while (true) {
		if (this->playing.size() == 0) {
			std::cout << "DEBUG game.cpp:32 " << this->playing.size() << std::endl;
			break;
		}

		for ( auto bot_pt = this->playing.begin(); bot_pt < this->playing.end(); bot_pt++ ) {
			system("clear");
			display::topLayer(this->game_world);
			for ( auto& bot : this->bots ) {
				display::botStats(bot);
			}

			if (!(*bot_pt)->canMove()) {
				std::cout << "DEBUG game.cpp:44 " << (*bot_pt)->canMove() << std::endl;
				this->playing.erase(bot_pt);
				continue;
			}

			(*bot_pt)->makeMove();
			(*bot_pt)->extract();

			std::cout << "  [ Press enter to continue... ]  ";
			std::cin.get();
		}

	}

	std::cout << "DEBUG game.cpp:58 " << this->bots.size() << std::endl;
	this->winner = *(std::max_element(this->bots.begin(), this->bots.end())); // TODO: fix

	delete game_world;
}