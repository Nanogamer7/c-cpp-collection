#ifndef NAIL_H
#define NAIL_H

#include "move.h"

enum nail_type {
    nail, needle,
};

class nail : public move
{
    public:

        nail(int damage, int soul, enum nail_type type);
        virtual ~nail();

        bool use(character* source, character* target) override;
};

#endif // NAIL_H
