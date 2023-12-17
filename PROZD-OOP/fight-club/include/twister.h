#ifndef TWISTER_H
#define TWISTER_H

#include "charm.h"

class twister : public charm {
	public:
	
		twister(int reduction) : reduction(reduction) {
            this->name = lang::STR_CHARM_TWISTER_NAME;
            this->descr = lang::STR_CHARM_TWISTER_DESCR;
        };
		~twister();

        int spellMod(int cost, dmg_type type, character* source, character* target) override;
	
	protected:

        const int reduction;
	
};

#endif