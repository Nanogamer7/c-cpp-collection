#ifndef DIVE_H
#define DIVE_H

#include "spell.h"

class dive : public spell {
	public:
	
		dive(int damage, int cost);
		~dive();

        void castSpell(character* source, character* enemies);

	protected:
        
        int speed = 9999; // high number for basically no chance of next atack hitting
};

#endif