#include <iostream>

#include "thorns.h"

thorns::~thorns()
{
    //dtor
}

int thorns::defMod(int damage, dmg_type type, character* source, character* target)
{
    if (type != melee) {
        return damage;
    }

    target->doDamage(this->damage, proc, source);
    std::cout << source->strName() << lang::STR_GENERIC__PROC_ << this->getName() << ". ";
}