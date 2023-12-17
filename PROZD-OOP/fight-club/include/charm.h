#ifndef CHARM_H
#define CHARM_H

#include "lang.h"

class charm
{
    public:

        virtual ~charm();

        virtual void reset() {};
        
        virtual int atkMod(int damage, dmg_type type, character* source, character* target) { return damage; };
        virtual int defMod(int damage, dmg_type type, character* source, character* target) { return damage; };
        virtual int spellMod(int cost, dmg_type type, character* source, character* target) { return cost; };
        virtual void turnMod(character* source) {};

        std::string getName() const { return name; };
        std::string getDescr() const { return descr; };

        virtual bool pseudoCharm() const { return false; };

    protected:
        
        std::string name;
        std::string descr;

    private:
};

#endif // CHARM_H
