#include "dash.h"

dash::dash(int damage, int speed, int soul, enum dash_type type) 
{
	this->damage = damage;
	this->speed = speed;
	this->soul = soul;

	this->name = lang::STR_MOVE_DASH_NAME[(int) type];
	this->descr = lang::STR_MOVE_DASH_DESCR[(int) type];

	this->type = targeted;
}

dash::~dash() {}

bool dash::use(character* source, character* target) 
{
	source->modSpeed(this->speed);

    int damage = static_cast<int>(this->damage * source->getStrength() / 100);
    bool success = source->doDamage(damage, melee, target);

    if (success) {
        source->useSoul(this->soul * (-1));    	
    } else {
		source->modSpeed((int) (this->speed * (-1.5)));
    }

    return true;
}