#include "fury.h"

fury::~fury() {}

void fury::turnMod(character* source) 
{
	source->modStrength(source->getStrengthBase() * (100 - (source->getHealth() < source->getHealthMax() ? (100 * source->getHealth() / source->getHealthMax()) : 100)) * this->scaling / 100 / 100);
}