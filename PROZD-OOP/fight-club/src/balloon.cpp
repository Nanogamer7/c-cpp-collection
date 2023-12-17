#include "balloon.h"

balloon::balloon(int damage, int cost)
{	
	this->name = lang::STR_MOVE_LOON_NAME;
	this->descr = lang::STR_MOVE_LOON_DESCR;
	
	this->damage = damage;
	this->cost = cost;

	this->type = self;
}

balloon::~balloon() {}

void balloon::castSpell(character* source, team* enemies)
{
	if (rand() % 2) {
		std::vector<character*> enemies_v = enemies->getMembers();
    	source->doDamage(this->damage, ranged, enemies_v.at(rand() % enemies_v.size()));
	} else {
		std::vector<character*> allies_v = enemies->getMembers();
		source->doDamage(this->damage * (-1), heal, allies_v.at(rand() % allies_v.size()));
	}
}