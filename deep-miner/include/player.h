#ifndef PLAYER_H
#define PLAYER_H

#include "bot.h"

class player : public bot {
public:

	player(int fuel, std::string name, class refinery* refinery, class drill* drill, class ability* ability)
	: bot(fuel, name, refinery, drill, ability) {};
	~player();

	std::string strName() override { return this->name + " (you)"; };

	void makeMove();
	
};

#endif