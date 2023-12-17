#include "enemy.h"
#include "decision.h"
#include "arena.h"
#include "player.h"

void enemy::decision()
{
	// ai controlled action

	this->tree->createTree(this, this->allied_team->getFight()->getOpponentTeam(this->allied_team)->getMembers(), this->getMoves());
	this->tree->decide();
}

void enemy::death()
{
	// on death

	this->allied_team->death(this);
	std::cout << this->name << " " << lang::STR_GENERIC_DIE << std::endl; // temporary
}