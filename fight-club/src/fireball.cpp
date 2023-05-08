#include "fireball.h"

fireball::fireball(int damage, int cost, enum fireball_type type)
{
    this->name = lang::STR_MOVE_FIREBALL_NAME[(unsigned long) type];
    this->descr = lang::STR_MOVE_FIREBALL_DESCR[(unsigned long) type];
    
    this->damage = damage;
    this->cost = cost;

    this->type = targeted;
}

fireball::~fireball()
{
    //dtor
}

void fireball::castSpell(character* source, character* target)
{
    source->doDamage(this->damage, ranged, target);
}