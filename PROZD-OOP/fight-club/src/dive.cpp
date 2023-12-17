#include "dive.h"

dive::dive(int damage, int cost) {

    this->name = lang::STR_MOVE_DIVE_NAME;
    this->descr = lang::STR_MOVE_DIVE_DESCR;
    
    this->damage = damage;
    this->cost = cost;

    this->type = area;
}

dive::~dive() {}

void dive::castSpell(character* source, character* enemies)
{
    for ( auto& target : enemies->getTeam()->getMembers()) {
        source->doDamage(this->damage, ranged, target); // will bug damage done string
    }
    source->modSpeed(this->speed);
}