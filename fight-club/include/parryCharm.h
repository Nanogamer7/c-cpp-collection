#ifndef PARRYCHARM_H
#define PARRYCHARM_H

#include "charm.h"

class parryCharm : public charm {
	
	public:

        parryCharm() {};
        
        int defMod(int damage, dmg_type type, character* source, character* target) override;

        bool pseudoCharm() const override { return true; };

    protected:

        const std::string name = "";
        const std::string descr = "";
};

#endif