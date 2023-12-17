#ifndef BALLOON_H
#define BALLOON_H

#include "spell.h"

class balloon : public spell{
	public:

		balloon(int damage, int cost);
		~balloon();

        void castSpell(character* source, team* enemies);

    protected:

        std::string name = lang::STR_MOVE_LOON_NAME;
		std::string descr = lang::STR_MOVE_LOON_DESCR;
};

#endif