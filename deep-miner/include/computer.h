#ifndef COMPUTER_H
#define COMPUTER_H

#include "bot.h"

class computer : public bot {
public:

	computer(int fuel, std::string name, class refinery* refinery, class drill* drill, class ability* ability)
	: bot(fuel, name, refinery, drill, ability) {};
	~computer();
	
	void makeMove();
};

#endif