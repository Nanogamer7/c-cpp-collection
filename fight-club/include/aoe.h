#ifndef AOE_H
#define AOE_H

#include "spell.h"

enum aoe_type {
	spew,
	cascade,
};

class aoe : public spell {
	public:
		
        aoe(int damage, int soul, enum aoe_type name);
		~aoe();

        void castSpell(character* source, character* enemies) override;

	protected:

        std::string name;
        std::string descr;
};

#endif