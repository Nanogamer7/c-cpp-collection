#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class player : public character
{
	public:
    	using character::character;
        void decision() override;

        std::string strName() const override;

        void printMoves() const;
        void printTargets() const;

    private:

		void death() override;
	
};

#endif