#include "parry.h"
#include "parryCharm.h"

parry::parry()
{
    this->name = lang::STR_MOVE_PARRY_NAME;
    this->descr = lang::STR_MOVE_PARRY_DESCR;

    this->is_parry = true;
}

parry::~parry() {}

bool parry::use(character* source, character* target) 
{
	source->addCharm(new parryCharm());
	return true;
}