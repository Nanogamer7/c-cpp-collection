#ifndef FURY_H
#define FURY_H

#include "charm.h"

class fury : public charm {
	public:
	
		fury(int scaling) : scaling(scaling) {
            this->name = lang::STR_CHARM_FURY_NAME;
            this->descr = lang::STR_CHARM_FURY_DESCR;
        };
		~fury();

        void turnMod(character* source) override;

	protected:

        const int scaling; // multiplier for damage scaling
	
};

#endif