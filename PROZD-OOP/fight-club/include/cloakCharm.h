#ifndef CLOAKCHARM_H
#define CLOAKCHARM_H

#include "charm.h"

class cloakCharm : public charm {

	public:

        cloakCharm(int speed) : speed(speed) {};
        
        void turnMod(character* source) override;

        bool pseudoCharm() const override { return true; };

    protected:

        const std::string name = "";
        const std::string descr = "";
        
    	int speed;
};

#endif