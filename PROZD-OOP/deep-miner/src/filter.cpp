#include "filter.h"

filter::filter() {}

filter::~filter() {}

void filter::use(struct coords coords, world* target) 
{
	auto column = target->getColumn(coords);
	int pumped = 0;
	for ( auto& gas : column ) {
		if (gas <=  0)
			continue;
		pumped++;
		gas--;
	}
	column.push_back(pumped);

	target->setColumn(coords, column);
}