#include "pump.h"

pump::pump() {}

pump::~pump() {}

void pump::use(struct coords coords, world* target) 
{
	auto column = target->getColumn(coords);
	std::sort(column.begin(), column.end());

	target->setColumn(coords, column);
}