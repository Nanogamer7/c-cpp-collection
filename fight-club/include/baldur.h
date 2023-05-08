#ifndef BALDUR_H
#define BALDUR_H

#include "charm.h"

class baldur : public charm {

	public:
	
		baldur(int shield) : max_shield(shield) {
            this->name = lang::STR_CHARM_BALDUR_NAME;
            this->descr = lang::STR_CHARM_BALDUR_DESCR;
        };
		~baldur();

        std::string getName() const;

        void reset() override;

        int defMod(int damage, dmg_type type, character* source, character* target) override;
        int spellMod(int cost, dmg_type type, character* source, character* target) override;
	
	protected:

        int max_shield;
        int shield;
        bool active = false;

};

#endif