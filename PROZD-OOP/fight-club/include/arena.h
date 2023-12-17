#ifndef ARENA_H
#define ARENA_H

#include "team.h"

class arena
/*
 * --- Arena contoller class ---
 *
 * Handles character deaths and turns
 *
 */
{

	public:

		arena(team* attacker, team* defender);
		~arena();

		bool fight();
		void lose(team* loser);
		void gameOver();

		void printStats();

		team* getOpponentTeam(team* self) const;
	
	protected:
		
		bool player_alive; // maybe a better solution?

		// relative to player
		team* allies;
		team* enemies;

		team* winner;
		team* loser;
};

#endif