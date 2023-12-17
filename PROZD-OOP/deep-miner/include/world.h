#ifndef WORLD_H
#define WORLD_H

#include "definitions.h"

#include <cstddef>
#include <cstdlib>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>

class bot;

class world
{
	public:

		world();
		~world();

		std::array<std::array<std::vector<int>, WORLD_SIZE_Y>, WORLD_SIZE_X> getGameWorld() { return this->game_world; };
		std::array<std::array<int, WORLD_SIZE_Y>, WORLD_SIZE_X> getTopLayer();
		std::array<std::array<bot*, WORLD_SIZE_Y>, WORLD_SIZE_X>& getSurfaceLayer() { return this->surface_layer; };
		std::vector<int>& getColumn(struct coords coords) { return this->game_world.at(coords.x).at(coords.y); };

		void fillWorld(unsigned int seed);
		void rearrangeWorld();
		void setColumn(struct coords coords, std::vector<int> new_column);
		struct coords findLowPoint(struct coords coords);

		void addBot(bot* bot, struct coords coords);
		coords moveBot(bot* bot, struct coords coords, struct coords new_coords);

		int extract(struct coords coords, int depth);

	private:

		std::array<std::array<std::vector<int>, WORLD_SIZE_Y>, WORLD_SIZE_X> game_world;
		std::array<std::array<bot*, WORLD_SIZE_Y>, WORLD_SIZE_X> surface_layer;

};

#endif