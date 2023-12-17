#include "charm.h"
#include "decision.h"
#include "arena.h"
#include "character.h"

character::character(std::string name, int health, int strength, int soul, int speed)
		: name(name), health(health), max_health(health), strength(strength), strength_mod(0),
			soul(soul), max_soul(soul), speed(speed), speed_mod(0)
{}

character::~character()
{
	for (auto& move : this->moves) {
		delete move;
	}

	for (auto& charm : this->charms) {
		delete charm;
	}

	if (this->tree != nullptr) {
		// delete this->tree;
	}
}

std::string character::strName() const
{
	return this->name;
}

std::string character::strHealth() const 
{
	if (this->health <= 0)
		return lang::STR_GENERIC_DEAD;
	return std::to_string(this->health) + "/" + std::to_string(this->max_health) + " " + lang::STR_GENERIC_HEALTH;
}

std::string character::strSoul() const 
{
	return std::to_string(this->soul) + "/" + std::to_string(this->max_soul) + " " + lang::STR_GENERIC_SOUL;
}

void character::turnStart()
{
	this->speed_mod = 0;
	this->strength_mod = 0;

	for (auto charm : this->charms) {
		charm->turnMod(this);
	}

	// this line of code is very cool 8)
	this->charms.erase(std::remove_if(this->charms.begin(), this->charms.end(), [](charm* c){ return c->pseudoCharm() ? (delete c, true) : false; }), this->charms.end());
}

void character::action() 
{
	if (this->allied_team->getFight()->getOpponentTeam(this->allied_team)->getMembers().size() == 0)
		return;
	this->decision();
}

void character::reset() 
{
	this->health = this->max_health;
	this->soul = this->max_soul;

	for (auto& charm : this->charms) {
		charm->reset();
	}

	this->charms.erase(std::remove_if(this->charms.begin(), this->charms.end(), [](charm* c){ return c->pseudoCharm() ? (delete c, true) : false; }), this->charms.end());
}

bool character::addMove(move* move)
{
	this->moves.push_back(move);

	return true; // TODO: max amount of abilities
}

bool character::addCharm(charm* charm) 
{
	this->charms.push_back(charm);

	return true; // TODO: max amount of charms
}

void character::printDodge() const
{
	std::cout << lang::STR_GENERIC_MISS << std::endl;
}

bool character::takeDamage(int damage, enum dmg_type type, character* source)
{
	// call defMod function for all charms
	switch (type)
	{
	case melee:
		if ( rand() % 100 > 100 * 100 / (( this->getSpeed() > source->getSpeed() / 2 ? (this->getSpeed() - source->getSpeed() / 2) : 0 ) + 100 )) {
			printDodge();
			return false;
		}
	case ranged:
		if ( rand() % 100 > 100 * 100 / ( this->getSpeed() / 2 + 100 )) {
			printDodge();
			return false;
		}
	default: ;
	}

	if ( type == melee || type == ranged ) {
		for (auto charm : this->charms) {
			charm->defMod(damage, type, source, this);
		}
	}

	if ( type == heal ) {
		std::cout << lang::STR_GENERIC_HEAL_ << std::to_string(damage * (-1)) << " " << lang::STR_GENERIC_HEALTH << "." << std::endl;
	} else {
		std::cout << lang::STR_GENERIC_DEAL_ << std::to_string(damage) << lang::STR_GENERIC__DMG << "." << std::endl;
	}

	this->health = this->health - damage < this->max_health ? this->health - damage : this->max_health;
	if ( this->health <= 0 )
		this->death();

	return true;
}

bool character::doDamage(int damage, enum dmg_type type, character* target)
{
	// call atkmod function for all charms
	for (auto& charm : this->charms) {
		charm->atkMod(damage, type, this, target);
	}

	return target->takeDamage(damage, type, this);
}

bool character::useSoul(int soul)
{
	if (soul < 0)
		this->soul = this->soul + soul * (-1) < this->max_soul ? this->soul + soul * (-1) : this->max_soul;
	else if (soul > this->soul)
		return false;
	else
		this->soul -= soul;

	return true;
}