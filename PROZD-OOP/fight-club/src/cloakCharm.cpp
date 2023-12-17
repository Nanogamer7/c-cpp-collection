#include "cloakCharm.h"

void cloakCharm::turnMod(character* source) 
{
	source->modSpeed((int) (this->speed * 0.7));
}