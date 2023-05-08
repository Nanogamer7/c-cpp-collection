#ifndef DASH_H
#define DASH_H

#include "move.h"

enum dash_type {
	lunge,
	lance,
	roll,
	slash,
	dive,
	uppercut,
};

class dash : public move {
	public:
	
		dash(int damage, int speed, int soul, enum dash_type type);
		~dash();
        
        bool use(character* source, character* target) override;
};

#endif