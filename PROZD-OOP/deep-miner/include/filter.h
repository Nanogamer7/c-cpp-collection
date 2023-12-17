#ifndef FILTER_H
#define FILTER_H

#include "ability.h"

class filter : public ability {
public:

	filter();
	~filter();

	void use(struct coords coords, world* target);
	
};

#endif