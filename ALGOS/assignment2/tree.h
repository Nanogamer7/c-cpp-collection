//
// Created by nano on 4/6/23.
//

#ifndef CODING2_TREE_H
#define CODING2_TREE_H


#include <vector>

class tree {
private:
    struct stats {
        int low;
        int high;
        int sum = 0;
        int count = 0;
    };
    struct node {
        node* left;
        node* right;
        // could use lambda function to determine next node

        int value;
    };

    struct stats stats = stats;
    node* head = nullptr;
    bool avl = true;

public:
    tree(const std::vector<int>& inputT);
    ~tree() = default;;

    void addValue(int value);
    void searchTree(tree* subT);
    std::vector<int> searchTreeRec(node* head, node* search);

    bool isAVL(node *tree);
    bool isAVL();
    int balance(node* tree);
};


#endif //CODING2_TREE_H
