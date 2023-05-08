#ifndef FIREBALL_H
#define FIREBALL_H

#include "spell.h"

enum fireball_type {
    fireball,
    bats,
};

class fireball : public spell
{
    public:

        fireball(int damage, int cost, enum fireball_type type);
        ~fireball();

        void castSpell(character* source, character* target) override;
        
};

#endif // FIREBALL_H
