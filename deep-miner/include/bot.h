#ifndef BOT_H
#define BOT_H

#include "refinery.h"
#include "drill.h"

class bot {
	public:

		bot(int fuel, std::string name, refinery* refinery, drill* drill, ability* ability) : 
			fuel(fuel), max_fuel(fuel), score(0),
			name(name),
			refinery(refinery),
			drill(drill),
			ability(ability) {};
		virtual ~bot();

		void setCoords(struct coords coords) { this->coords = coords; };
		void setWorld(world* world) { this->game_world = world; };

		bool canMove();
		virtual void makeMove() = 0;
		void move(struct coords coords);
		void extract();

		void leakFuel() { this->fuel -= this->fuel / 3; };
		void breakDrill() { this->defect = true; };

		int getScore() { return this->score; };
		std::string getName() { return this->name; };

		virtual std::string strName() { return this->name; };
		std::string strScore() { return std::to_string(this->score); };
		std::string strFuel() { return std::to_string(this->fuel) + "/" + std::to_string(this->max_fuel); };

		bool operator<(bot* bot) { // TODO: fix - see game.cpp:58
			return score < bot->score;
		}

	protected:

		class world* game_world;
		struct coords coords;

		int fuel;
		int max_fuel;
		int score;
		std::string name;

		class refinery* refinery;
		class drill* drill;
		class ability* ability;

		bool defect = false;
};

#endif