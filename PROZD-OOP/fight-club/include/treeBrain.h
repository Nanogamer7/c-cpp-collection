#ifndef TREEBRAIN_H
#define TREEBRAIN_H

#include "decision.h"

class treeBrain : public decision {
	public:

		treeBrain() {};

		void createTree(character* self, std::vector<character *> targets, std::vector<move *> moves) {
			this->addContext(self, targets, moves);

			// this tree assumes each character only has max one spell, and all other moves gain soul
			Node* canCastSpell = this->newNode(moves.at(0)->getCost(), 0, &treeBrain::findSpell);
			Node* hasParry = this->newNode(moves.at(0)->getParry() ? 1 : -1, 0, &treeBrain::findParry);
			Node* needParry = this->newNode((*std::min_element(targets.begin(), targets.end()))->getSpeed(), self->getSpeed() * (2 + 100 * self->getHealth() / self->getHealthMax() / 100), nullptr);

			this->head = canCastSpell;
			addFailed(canCastSpell, hasParry);
			addSuccess(hasParry, needParry);
		};

		~treeBrain() {
			
		};

	private:
		
		static void removeNoSoul(character*& curr_self, std::vector<character *>& targets, std::vector<move *>& moves) {
			moves.erase(std::remove_if(moves.begin(), moves.end(), [=](move* c){ return c->getCost() > curr_self->getSoul(); }), moves.end());
		}

		static void findSpell(character*& curr_self, std::vector<character *>& targets, std::vector<move *>& moves) {
			auto has_cost = [](const auto& move) {
    			return move->getCost() != 0;
			};
			auto find = std::find_if(moves.begin(), moves.end(), has_cost);
			if (find != moves.end()) {
				std::rotate(moves.begin(), find, find+1);
			}
		}

		static void findParry(character*& curr_self, std::vector<character *>& targets, std::vector<move *>& moves) {
			auto is_parry = [](const auto& move) {
    			return move->getParry();
			};
			auto find = std::find_if(moves.begin(), moves.end(), is_parry);
			if (find != moves.end()) {
				std::rotate(moves.begin(), find, find+1);
			}
		}
};

#endif