#include "cloak.h"
#include "cloakCharm.h"

cloak::cloak(int speed) {

    this->name = lang::STR_MOVE_CLOAK_NAME;
    this->descr = lang::STR_MOVE_CLOAK_DESCR;

	this->speed = speed;
	this->type = self;
};

cloak::~cloak() {}

bool cloak::use(character* source, character* target) 
{
	source->modSpeed(this->speed);
	source->addCharm(new cloakCharm(this->speed));

	return true;
}