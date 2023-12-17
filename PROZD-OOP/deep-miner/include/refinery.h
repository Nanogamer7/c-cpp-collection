#ifndef REFINERY_H
#define REFINERY_H

#include "ability.h"

class refinery {

	public:

		refinery(int efficiency) : efficiency(efficiency) {
			std::cout << "DEBUG refinery.h:11" << std::endl;
		};
		~refinery();

		int use(int extracted) { return extracted * efficiency / 100; };
	
	private:

		int efficiency;
		
};

#endif