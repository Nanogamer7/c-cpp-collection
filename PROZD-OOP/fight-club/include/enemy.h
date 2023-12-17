#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

enum tree_type {
	greed,
	dumb,
	brain
};

class enemy : public character
{
	public:

    	using character::character;
        void decision() override;

    private:
    	
		void death() override;
};

#endif