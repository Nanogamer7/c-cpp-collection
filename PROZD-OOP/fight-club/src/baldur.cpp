#include "baldur.h"

baldur::~baldur() {}

std::string baldur::getName() const 
{
	return this->name + " (" + std::to_string(this->shield) + "/" + std::to_string(this->max_shield) + " " + lang::STR_GENERIC_SHIELD + ")";
}

void baldur::reset() 
{
	this->shield = this->max_shield;
}

int baldur::defMod(int damage, dmg_type type, character* source, character* target) 
{
	if (this->active == false)
		return damage;

	this->shield -= damage;
	return 0;
}

int baldur::spellMod(int cost, dmg_type type, character* source, character* target) 
{
	if (type == heal && this->shield > 0)
		this->active = true;
	return cost;
}