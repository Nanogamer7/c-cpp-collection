#ifndef GRUB_H
#define GRUB_H

#include "charm.h"

class grub : public charm {
	public:
	
		grub(int soul) : soul(soul) {
            this->name = lang::STR_CHARM_GRUBS_NAME;
            this->descr = lang::STR_CHARM_GRUBS_DESCR;
        };
		~grub();

        int defMod(int damage, dmg_type type, character* source, character* target) override;
	
	protected:

        const int soul;
	
};

#endif