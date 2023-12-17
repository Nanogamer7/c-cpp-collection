#include "twister.h"

twister::~twister() {}

int twister::spellMod(int cost, dmg_type type, character* source, character* target) 
{
	return cost - this->reduction > 0 ? cost - this->reduction : 0;
}