#ifndef GAME_H
#define GAME_H

#include "world.h"

class game {

	public:

		game();
		~game();

		void addBot(bot* bot) { this->bots.push_back(bot); };
		void startGame();
		bot* getWinner() { return this->winner; };

	private:

		world* game_world;
		std::vector<bot*> bots;
		std::vector<bot*> playing;

		bot* winner = nullptr;
	
};

#endif