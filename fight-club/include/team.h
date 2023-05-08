#ifndef TEAM_H
#define TEAM_H

class arena;

#include "character.h"

class team {
	public:

		team();
		~team();
		void deleteMembers();

		void turnStart();
		void action();
		void death(character* character);
		void win();

		std::vector<character*> getMembers() const;
		arena* getFight() const;

		void addMember(character* character);
		void setFight(arena* arena);

	protected:

		std::vector<character*> members;
		arena* fight;

		void sortBySpeed();
};

#endif