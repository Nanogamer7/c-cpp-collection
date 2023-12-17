#include <iostream>
#include <vector>
#include "tree.h"
#include <fstream>

std::vector<int> readFile(const std::string& path);

int main(int argc, char *argv[]) {
    if (argc < 2)
        return 0;

    tree* mainT = new class tree(readFile(std::string(argv[1])));
    mainT->isAVL();

    if (argc < 3)
        return 0;

    tree* subT = new class tree(readFile(std::string(argv[2])));
    mainT->searchTree(subT);

    return 0;
}

std::vector<int> readFile(const std::string& path)
{
    std::vector<int> list;

    std::ifstream input(path);
    for( std::string line; getline( input, line );) {
        list.push_back(std::stoi(line));
    };

    return list;
}
