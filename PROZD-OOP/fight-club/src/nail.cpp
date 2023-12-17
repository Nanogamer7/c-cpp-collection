#include "nail.h"

nail::nail(int damage, int soul, enum nail_type type)
{
    this->name = lang::STR_MOVE_NAIL_NAME[(int) type];
    this->descr = lang::STR_MOVE_NAIL_DESCR[(int) type];

    this->damage = damage;
    this->soul = soul;

    this->type = targeted;
}

nail::~nail()
{
    //dtor
}

bool nail::use(character* source, character* target)
{
    int damage = static_cast<int>(this->damage * source->getStrength() / 100);
    bool success = source->doDamage(damage, melee, target);

    if (success)
        source->useSoul(this->soul * (-1));

    return true;
}
