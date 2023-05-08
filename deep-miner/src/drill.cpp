#include "drill.h"

drill::~drill() {}

int drill::use(struct coords coords, world* target) 
{
	std::cout << "DEBUG drill.cpp:7 " << this->depth << std::endl;
	return target->extract(coords, this->depth);
}