#include <iostream>
#include <algorithm>

#include "arena.h"
#include "team.h"

team::team()
{

}

team::~team()
{
	
}

void team::deleteMembers()
{
	std::cout << "debug: " << std::to_string(members.size()) << std::endl;
	for (auto& member : this->members) { // not working
		delete member;
	}
}

std::vector<character*>	team::getMembers() const { return this->members; }
arena* 					team::getFight() const { return this->fight; }

void team::setFight(arena* arena) { this->fight = arena; }

void team::addMember(character* character)
{
	this->members.push_back(character);
	character->setTeam(this);
}

void team::turnStart() 
{
	this->sortBySpeed();
	for (auto& member : this->members) {
		if (member->getHealth() > 0)
			member->turnStart();
	}
}

void team::action() 
{
	this->sortBySpeed();
	for (auto& member : this->members) {
		if (member->getHealth() > 0)
			member->action();
	}
}

void team::death(character* character) 
{
    auto member = std::find(this->members.begin(), this->members.end(), character);
    if (member != this->members.end()) {
        this->members.erase(member);
    }

    if (this->members.empty()) {
        this->fight->lose(this);
    }
}

void team::sortBySpeed() 
{
	std::min_element(this->members.begin(), this->members.end(), std::less<>());
}

void team::win() 
{
	for ( auto& member : this->members ) {
		member->reset();
	}
}