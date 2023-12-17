#ifndef PUMP_H
#define PUMP_H

#include "ability.h"

class pump : public ability {
public:

	pump();
	~pump();
	
	void use(struct coords coords, world* target);
};

#endif