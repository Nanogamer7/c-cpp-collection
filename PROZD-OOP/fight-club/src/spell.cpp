#include "spell.h"

bool spell::use(character* source, character* target)
{
    if (source->useSoul(this->cost)) {
        this->castSpell(source, target);
        return true;
    }
    
    return false;
}
