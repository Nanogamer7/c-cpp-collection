#include "bot.h"

world::world() {}

world::~world() {}

std::array<std::array<int, WORLD_SIZE_Y>, WORLD_SIZE_X> world::getTopLayer() 
{
	std::array<std::array<int, WORLD_SIZE_Y>, WORLD_SIZE_X> topLayer;
	for (int i = 0; i < WORLD_SIZE_X * WORLD_SIZE_Y; i++) {
		auto x = i / WORLD_SIZE_X;
		auto y = i % WORLD_SIZE_Y;
		auto& column = this->game_world[x][y];
		topLayer[x][y] = column.size() > 0 ? this->game_world[x][y].back() : 10;
	}

	return topLayer;
}

void world::fillWorld(unsigned int seed) 
{
	srand(seed);

	std::array<std::array<int, WORLD_SIZE_Y>, WORLD_SIZE_X> topLayer;
	for (int i = 0; i < WORLD_SIZE_X * WORLD_SIZE_Y; i++) {
		auto x = i / WORLD_SIZE_X;
		auto y = i % WORLD_SIZE_Y;

		std::vector<int> column;
		for (int i = 0; i <= WORLD_SIZE_Z; i++) {
			column.push_back((int) ((2 - log10((float) (100 - rand()%57))) * 25 + 1)); // semi arbitrary values to get a nice distribution
		}

		// Only one trap per type per column

		if (rand()%100 < 8)
			column.at(rand()%column.size()) = -1;

		if (rand()%100 < 8)
			column.at(rand()%column.size()) = -2;

		if (rand()%100 < 8)
			column.at(rand()%column.size()) = -3;

		this->game_world[x][y] = column;
		this->surface_layer[x][y] = nullptr;
	}
}

void world::rearrangeWorld() 
{
	auto extractEffects = [](std::vector<int>& input) -> std::vector<int> {
		std::vector<int> effects;
		input.erase(std::remove_if(input.begin(), input.end(), [&effects](int val) {
			if (val < 0) {
				effects.push_back(val);
				return true;
			}
			return false;
		}), input.end());
		return effects;
	};

	for (unsigned long i = 0; i < WORLD_SIZE_X * WORLD_SIZE_Y; i++) {
		auto& column = this->game_world[i / WORLD_SIZE_X][i % WORLD_SIZE_Y];

		auto effects = extractEffects(column);

		switch (static_cast<world_action>(rand()%3)) {
			case shuffle:
				std::shuffle(column.begin(), column.end(), std::default_random_engine{});
				break;
			case sort_desc:
				std::sort(column.begin(), column.end(), std::greater<>());
				break;
	   		case sort_asc:
				std::sort(column.begin(), column.end());
				break;
		}
		
		for (auto& effect : effects) {
			column.insert(column.begin() + rand()%column.size(), effect);
		}
	}
}

void world::setColumn(struct coords coords, std::vector<int> new_column) 
{
	this->game_world[coords.x][coords.y] = new_column;
}

void world::addBot(bot* bot, struct coords coords) 
{
	this->surface_layer[coords.x][coords.y] = bot;
}

coords world::moveBot(bot* bot, struct coords old_coords, struct coords new_coords) 
{
	this->surface_layer[old_coords.x][old_coords.y] = nullptr;
	auto& column = this->getColumn(new_coords);
	auto trap = std::find_if(column.rbegin(), column.rend(), [](int x) { return x < 0; });
	enum trap_type type = static_cast<enum trap_type>(trap == column.rend() ? 0 : (*trap) * (-1));
	std::cout << "DEBUG world.cpp:106 " << new_coords.x << "," << new_coords.y << std::endl;
	switch (type) {
        case defect:
        	bot->breakDrill();
			break;
        case landslide:
        	new_coords = this->findLowPoint(new_coords);
			break;
        case leak:
        	bot->leakFuel();
			break;
    }
    if (trap != column.rend()) {
		std::cout << "DEBUG world.cpp:119 " << *trap << std::endl;
    	*trap = 0;
    }
	std::cout << "DEBUG world.cpp:122 " << new_coords.x << "," << new_coords.y << std::endl;
    this->addBot(bot, new_coords);

    return new_coords;
}

coords world::findLowPoint(struct coords coords) 
{
	auto topLayer = this->getTopLayer();

	int lowest = 10;
	struct coords low_coords;
	struct coords new_coords;
	for (int i = 0; i < 10; i++) {
		new_coords = { coords.x + (i / 3) - 1, coords.y + (i % 3) - 1 };
		if (new_coords.x < 0 ||
			new_coords.y < 0 ||
			new_coords.x >= WORLD_SIZE_X ||
			new_coords.y >= WORLD_SIZE_Y)
			continue;

		if (new_coords.x == coords.x && new_coords.y == coords.y)
			continue;

		if (this->surface_layer[new_coords.x][new_coords.y] != nullptr) {
			continue;
		}

		if (topLayer[new_coords.x][new_coords.y] < lowest) {
			lowest = topLayer[new_coords.x][new_coords.y];
			low_coords = new_coords;
		}
	}

	return low_coords;
}

int world::extract(struct coords coords, int depth) 
{
	auto& column = this->game_world[coords.x][coords.y];
	int value = 0;
	for (int i = 0; i < depth; i++) {
		if (column.size() == 0)
			break;
		value += column.back();
		column.erase(column.end() - 1);
	}
	return value;
}