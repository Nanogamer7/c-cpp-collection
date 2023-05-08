#ifndef THORNS_H
#define THORNS_H

#include "charm.h"

class thorns : public charm
{
    public:

        thorns(int damage) : damage(damage) {
            this->name = lang::STR_CHARM_THORNS_NAME;
            this->descr = lang::STR_CHARM_THORNS_DESCR;
        };
        ~thorns();
        
        int defMod(int damage, dmg_type type, character* source, character* target) override;

    protected:
        
    	const int damage;

    private:
};

#endif // THORNS_H