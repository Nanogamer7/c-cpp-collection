#include "strength.h"

strength::~strength() {}

void strength::turnMod(character* source) 
{
	source->modStrength(this->mod);
}