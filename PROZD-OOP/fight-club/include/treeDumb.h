#ifndef TREEDUMB_H
#define TREEDUMB_H

#include "decision.h"

class treeDumb : public decision {
	public:

		treeDumb() {};

		void createTree(character* self, std::vector<character *> targets, std::vector<move *> moves) {
			this->addContext(self, targets, moves);

			this->head = newNode(1, 0, &treeDumb::removeNoSoul);
		};

		~treeDumb() {
			
		};

	private:
		
		static void removeNoSoul(character*& curr_self, std::vector<character *>& targets, std::vector<move *>& moves) {
			moves.erase(std::remove_if(moves.begin(), moves.end(), [=](move* c){ return c->getCost() > curr_self->getSoul(); }), moves.end());
		}
};

#endif