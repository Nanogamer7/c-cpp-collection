#ifndef DECISION_H
#define DECISION_H

#include <algorithm>
#include <iostream>
#include <random>

#include "move.h"

class decision
{
	protected: // forward
		struct Node {
			int value;
			int compare;
			void (*func)(character*&, std::vector<character *>&, std::vector<move *>&);
			Node* success;
			Node* fail;
		};

	public:
		decision() {};

		virtual ~decision() {
			if (head != nullptr)
				deleteNodes(head);
		}

		virtual void createTree(character* self, std::vector<character *> targets, std::vector<move *> moves) = 0;

		bool decide() {
			for (Node* node = head; (node->value >= node->compare ? node->success : node->fail) != nullptr; node = node->value >= node->compare ? node->success : node->fail) {
				if (node->func != nullptr)
					node->func(this->self, this->targets, this->moves);
			}

			move* move = this->moves.at(0);
			std::cout << self->strName() << " " << lang::STR_GENERIC_USE_ << move->getName() << ". ";
			if (move->getType() == targeted || move->getType() == area)
				return move->use(this->self, this->targets.at(0));
			else
				return move->use(this->self, nullptr);
		}

	protected:

		void addContext(character* self, std::vector<character *> targets,std::vector<move *> moves) {
			this->self = self;
			this->targets = targets;
			this->moves = moves;
			head = nullptr;
			std::random_device rd;
    		std::mt19937 g(rd());
			std::shuffle(this->targets.begin(), this->targets.end(), g);
			std::shuffle(this->moves.begin(), this->moves.end(), g);
		}

		void addSuccess(Node*& head, Node* newNode) {
			head->success = newNode;
		}

		void addFailed(Node*& head, Node* newNode) {
			head->fail = newNode;
		}

		Node* newNode(int value, int compare, void (*func)(character*&, std::vector<character *>&, std::vector<move *>&)) {
			Node* newNode = new Node();

			newNode->func = func;
			newNode->value = value;
			newNode->compare = compare;
			newNode->success = nullptr;
			newNode->fail = nullptr;

			return newNode;
		}

		Node* head;

		character* self;
		std::vector<character *> targets;
		std::vector<move *> moves;

	private:

		void deleteNodes(Node* node) {
			for ( auto child : { &node->success, &node->fail } ) {
				if (*child != nullptr) {
					deleteNodes(*child);
					child = nullptr;
				}
			}
		}
		
};

#endif