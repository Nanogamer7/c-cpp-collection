#ifndef ABILITY_H
#define ABILITY_H

#include "world.h"

class ability {
	public:

		ability();
		virtual ~ability();

		virtual void use(struct coords coords, world* target) = 0;
	
};

#endif