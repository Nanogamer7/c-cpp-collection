#ifndef PARRY_H
#define PARRY_H

#include "move.h"

class parry : public move {
	public:
	
		parry();
		~parry();
        
        bool use(character* source, character* target) override;

};

#endif