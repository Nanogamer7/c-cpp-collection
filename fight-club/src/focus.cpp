#include "focus.h"

focus::focus(int strength, int cost)
{

    this->name = lang::STR_MOVE_FOCUS_NAME;
    this->descr = lang::STR_MOVE_FOCUS_DESCR;
    
    this->strength = strength;
    this->cost = cost;

    this->type = self;
}

focus::~focus()
{
    //dtor
}

void focus::castSpell(character* source, character* target)
{
    source->takeDamage(this->strength * (-1), heal, source);
}