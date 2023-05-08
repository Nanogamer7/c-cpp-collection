#include <limits>

#include "arena.h"
#include "display.h"

arena::arena(team* attacker, team* defender)
    : allies(attacker), enemies(defender), winner(nullptr)
{
    attacker->setFight(this);
    defender->setFight(this);
}


arena::~arena()
{

}

team* arena::getOpponentTeam(team* self) const 
{
	return self == this->allies ? this->enemies : this->allies;
}

void arena::lose(team* lose)
{
	this->winner = this->allies == lose ? this->enemies : this->allies;
    this->loser = lose;
}

void arena::gameOver() 
{
	this->player_alive = false;
    this->winner = this->enemies;
}

bool arena::fight()
{
	std::vector<team*> combatants = { this->allies, this->enemies };
	for (int attack = 0; !this->winner; attack++) {
        combatants.at(attack % 2)->turnStart();
		display::displayFightStats(this->allies->getMembers(), this->enemies->getMembers());
		combatants.at(attack % 2)->action();
		// TODO: team functionality

		std::cout << std::endl << "   [" << lang::STR_COMBAT_ENTER_CONTINUE << "]" << std::endl;
		std::cin.ignore();
	}

    this->winner->win();

	bool return_val = this->player_alive;
	return return_val;
}