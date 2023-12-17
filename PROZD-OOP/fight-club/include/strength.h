#ifndef STRENGTH_H
#define STRENGTH_H

#include "charm.h"

class strength : public charm {

	public:
	
		strength(int strength) : mod(strength) {
            this->name = lang::STR_CHARM_STRENGTH_NAME;
            this->descr = lang::STR_CHARM_STRENGTH_DESCR;
        };
		~strength();

		void turnMod(character* source) override;
	
	protected:

        const int mod;
	
};

#endif