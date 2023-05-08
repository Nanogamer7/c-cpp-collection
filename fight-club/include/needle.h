#ifndef NEEDLE_H
#define NEEDLE_H

#include "move.h"

enum needle_type {
	needle_throw,
	blades,
};

class needle : public move {
	public:
	
		needle(int damage, enum needle_type type);
        ~needle();
        
        bool use(character* source, character* target) override;
};

#endif