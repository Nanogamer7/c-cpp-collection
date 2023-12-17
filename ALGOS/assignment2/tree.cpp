//
// Created by nano on 4/6/23.
//

#include <iostream>
#include <cmath>
#include <iomanip>

#include "tree.h"

tree::tree(const std::vector<int>& inputT)
{
    for ( int value : inputT ) {
        addValue(value);
    }
};

void tree::addValue(int value)
{
    node *node = new struct node();
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;

    if (this->head == nullptr) {
        this->head = node;
        for ( auto& i : { &this->stats.low, &this->stats.high } )
            *i = value;
        return;
    }

    struct node** next = &(this->head);
    for (; *next != nullptr; next = value < (*next)->value ? &((*next)->left) : &((*next)->right) );

    *next = node;
};

bool tree::isAVL(node *tree)
{
    using namespace std;

    this->balance(tree);

    cout << "AVL: ";
    this->avl ? cout << "Yes" : cout << "No" ;
    cout << endl;

    cout << "min: " << stats.low << ", ";
    cout << "max: " << stats.high << ", ";
    cout << "avg: " << std::fixed << std::setprecision(2) << (float) stats.sum/(float) stats.count << ", ";
    cout << endl;

    return avl;
};

bool tree::isAVL()
{
    return this->isAVL(this->head);
};

int tree::balance(node *tree) {
    int balance;

    int heightL = tree->left == nullptr ? 0 : this->balance(tree->left);
    int heightR = tree->right == nullptr ? 0 : this->balance(tree->right);

    balance = heightR - heightL;
    this->stats.sum += tree->value;
    this->stats.count++;
    this->stats.low = tree->value < this->stats.low ? tree->value : this->stats.low;
    this->stats.high = tree->value > this->stats.high ? tree->value : this->stats.high;

    std::cout << "bal(" << tree->value << ") = " << balance;
    if (std::abs(balance) > 1) {
        std::cout << " (AVL violation!)";
        this->avl = false;
    }
    std::cout << std::endl;

    return (heightL > heightR ? heightL : heightR) + 1;
}

void tree::searchTree(tree* subT) {
    using namespace std;

    bool singleNr = (subT->head->left == nullptr && subT->head->right == nullptr);
    std::vector<int> path = searchTreeRec(this->head, subT->head);
    // if searching for subtree, path acts as a boolean, not as the actual path
    if (singleNr) {
        cout << subT->head->value;
    } else {
        cout << "Subtree";
    }

    if (path.empty()) {
        cout << " not found!";
    } else {
        cout << " found";
    }

    if (singleNr) {
        for ( int i : path) {
            cout << ", " << i;
        }
    }

    cout << endl;
};

std::vector<int> tree::searchTreeRec(node* head, node* search) {
    std::vector<int> path = {};

    if (head->value == search->value) {
        if (search->left == nullptr && search->right == nullptr) {
            return { head->value };
        }
        if ((search->left == nullptr || !searchTreeRec(head, search->left).empty())
            && (search->right == nullptr || !searchTreeRec(head, search->right).empty()))
            path.push_back(1);
        return path;
    }

    auto next = [&]() {
        return (search->value < head->value ? head->left : head->right);
    };

    if (next() != nullptr) {
        path = searchTreeRec(next(), search);
        if (!path.empty()) {
            path.insert(path.begin(), head->value);
        }
    }

    return path;
};