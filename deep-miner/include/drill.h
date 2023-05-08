#ifndef DRILL_H
#define DRILL_H

#include "ability.h"

class drill {
	public:

		drill(int depth) : depth(depth) {
			std::cout << "DEBUG drill.h:11" << std::endl;
		};
		~drill();

		int use(struct coords coords, world* target);
	
	private:

		int depth;
};

#endif