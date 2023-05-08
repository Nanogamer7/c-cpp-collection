#ifndef FOCUS_H
#define FOCUS_H

#include "spell.h"


class focus : public spell
{
    public:

        focus(int heal, int soul);
        virtual ~focus();

        void castSpell(character* source, character* target) override;

    protected:
        
        int strength;

    private:
};

#endif // FOCUS_H
