#include "aoe.h"

aoe::aoe(int damage, int cost, enum aoe_type type) {
    this->name = lang::STR_MOVE_AOE_NAME[(unsigned long) type];
    this->descr = lang::STR_MOVE_AOE_DESCR[(unsigned long) type];

    this->damage = damage;
    this->cost = cost;

    this->type = area;
}

aoe::~aoe() {}


void aoe::castSpell(character* source, character* enemies)
{
    for ( auto& target : enemies->getTeam()->getMembers()) {
        source->doDamage(this->damage, ranged, target); // will bug damage done string
    }
}