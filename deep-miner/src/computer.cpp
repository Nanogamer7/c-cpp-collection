#include "computer.h"

computer::~computer() {}

void computer::makeMove() 
{
	std::vector<struct field_stats> fields;
	for (int i = 0; i < WORLD_SIZE_X * WORLD_SIZE_Y; i++) {
		struct coords new_coords = { i / WORLD_SIZE_X, i % WORLD_SIZE_Y };
		auto column = this->game_world->getColumn(new_coords);

		if (!column.empty())
			fields.push_back( { new_coords, std::abs(this->coords.x - new_coords.x) + std::abs(this->coords.y - new_coords.y), column.back() } );
	}

	std::sort(fields.begin(), fields.end(), std::greater<>());

	while (true) {
		try {
			this->move(fields.at(0).coords);
		} catch(char const* error) {
			fields.erase(fields.begin());
			continue;
		}
		break;
	}
}