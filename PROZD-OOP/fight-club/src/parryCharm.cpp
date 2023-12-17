#include <iostream>

#include "parryCharm.h"

int parryCharm::defMod(int damage, dmg_type type, character* source, character* target) 
{
	if (type != melee) {
		return damage;
	}

	target->doDamage(target->getStrength(), proc, source);
	std::cout << target->strName() << lang::STR_GENERIC__PARRY_ << target->strName() << lang::STR_GENERIC_SATACK_ << " " << lang::STR_GENERIC_AND_DEAL_;
	return 0;
}