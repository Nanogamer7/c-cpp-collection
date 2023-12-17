#ifndef TREEGREED_H
#define TREEGREED_H

#include "decision.h"

class treeGreed : public decision {
	public:

		treeGreed() {};

		void createTree(character* self, std::vector<character *> targets, std::vector<move *> moves) {
			this->addContext(self, targets, moves);

			this->head = newNode(1, 0, &treeGreed::removeNoSoul);
			addSuccess(this->head, newNode(1, 0, &treeGreed::sortLowestHP));
			addSuccess(this->head->success, newNode(1, 0, &treeGreed::sortHighestDamage));

		}

		~treeGreed() {
			
		};

	private:

		static void removeNoSoul(character*& curr_self, std::vector<character *>& targets, std::vector<move *>& moves) {
			moves.erase(std::remove_if(moves.begin(), moves.end(), [=](move* c){ return c->getCost() > curr_self->getSoul(); }), moves.end());
		}

		static void sortHighestDamage(character*& curr_self, std::vector<character *>& targets, std::vector<move *>& moves) {
			std::sort(moves.begin(), moves.end(), std::less<>());
		}

		static void sortLowestHP(character*& curr_self, std::vector<character *>& targets, std::vector<move *>& moves) {
			std::sort(targets.begin(), targets.end(), std::greater<>());
		}
};

#endif