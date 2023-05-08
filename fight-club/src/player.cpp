#include <iostream>

#include "move.h"
#include "arena.h"
#include "player.h"

void player::decision() 
{
	int select;
	character* target = nullptr;

	std::cout << lang::STR_COMBAT_CHOICE_MOVE << std::endl;
	this->printMoves();
	std::cin >> select;

	select--;
	select %= (int) this->moves.size();

	move* move = this->moves.at(select);
	if (move->getType() == targeted) {
		this->printTargets();
		std::cin >> select;
		select--;
		select %= (int) this->allied_team->getFight()->getOpponentTeam(this->allied_team)->getMembers().size();
		target = this->allied_team->getFight()->getOpponentTeam(this->allied_team)->getMembers().at(select);
	} else if (move->getType() == area) { // f-ed up parameters, too much work to fix, so here's a permanent temporary solution
		target = this->allied_team->getFight()->getOpponentTeam(this->allied_team)->getMembers().at(0);
	}
	std::cout << lang::STR_GENERIC_YOUC_ << lang::STR_GENERIC_USE_ << move->getName() << ". ";
	move->use(this, target);

	std::cin.ignore(); // scuffed af
}

void player::death() 
{
	// on death

	this->allied_team->getFight()->gameOver();
	this->allied_team->death(this);
	std::cout << "You are dead!" << std::endl; // temporary
}

std::string player::strName() const
{
	return this->name + " (" + lang::STR_GENERIC_YOU + ")";
}

void player::printMoves() const
{
	int opt_count = 1;
	for (auto& move : this->moves) {
		int cost = move->getCost();

		std::cout << "[" << opt_count << "]";
		if (cost > this->soul)
			std::cout << "[" << lang::STR_GENERIC_UNAVAILABLE << "]";
		std::cout << " " << move->getName();
		if (cost > 0)
			std::cout << " (" << cost << " " << lang::STR_GENERIC_SOUL << ")";
		std::cout << std::endl;

		opt_count++;
	}
}

void player::printTargets() const
{
	int opt_count = 1;

	std::cout << lang::STR_COMBAT_CHOICE_TARGET << std::endl;
	for (auto& target : this->allied_team->getFight()->getOpponentTeam(this->allied_team)->getMembers()) {
		std::cout << "[" << opt_count << "] " << target->strName() << " (" << target->strHealth() << ")" << std::endl;
		opt_count++;
	}	
}