#ifndef SPELL_H
#define SPELL_H

#include "move.h"

class spell : public move
{
    public:
        
        bool use(character* source, character* target) override;
        virtual void castSpell(character* source, character* target) = 0;

    protected:

    private:
};

#endif // SPELL_H
