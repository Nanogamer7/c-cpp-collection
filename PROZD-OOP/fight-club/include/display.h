#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <iomanip>

#include "enemy.h"
#include "player.h"
#include "charm.h"
#include "lang.h"

struct gameStats {
    int selected = 0;
    std::string name_knight;
    std::string name_hornet;
    std::string name_custom;
    int wins_knight;
    int wins_hornet;
    int wins_custom;
    int loses_knight;
    int loses_hornet;
    int loses_custom;
};

namespace display {

	void displayStrings(std::vector<std::string> options);
	void displayStats(struct gameStats gameStats);
	void displayPlayer(player* player, enemy* ally);
	void displayOptionsMain();
	void displayOptionsFight();
	void displayFightStats(std::vector<character *> allies, std::vector<character *> enemies);

}

#endif