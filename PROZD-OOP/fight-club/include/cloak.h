#ifndef CLOAK_H
#define CLOAK_H

#include "move.h"

class cloak : public move {
	public:

		cloak(int speed);
		~cloak();
        
        bool use(character* source, character* target) override;

};

#endif