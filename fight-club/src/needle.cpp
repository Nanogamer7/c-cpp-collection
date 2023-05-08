#include "needle.h"

needle::needle(int damage, enum needle_type type)
{
    this->name = lang::STR_MOVE_NTHROW_NAME[(int) type];
    this->descr = lang::STR_MOVE_NTHROW_DESCR[(int) type];

    this->damage = damage;

    this->type = targeted;
}

needle::~needle()
{
    //dtor
}

bool needle::use(character* source, character* target)
{
    int damage = static_cast<int>(this->damage * source->getStrength() / 100);
	source->doDamage(damage, ranged, target);

    return true;
}