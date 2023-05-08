#include "bot.h"

bot::~bot() {
	delete this->refinery;
	delete this->drill;
	delete this->ability;
}

bool bot::canMove() 
{
	bool move = false;

	for (int i = 0; i < WORLD_SIZE_X * WORLD_SIZE_Y; i++) {
		struct coords probe = { i / WORLD_SIZE_X, i % WORLD_SIZE_Y };

		if ((std::abs(this->coords.x-probe.x) + std::abs(this->coords.y-probe.y)) * 3 > this->fuel)
			continue;

		if (this->game_world->getSurfaceLayer()[probe.x][probe.y] != nullptr)
			continue;

		if (!this->game_world->getColumn(probe).empty()) {
			move = true;
			break;
		}
	}

	return move;
}

void bot::move(struct coords new_coords) 
{
	if ((new_coords.x) < 0 || (new_coords.x) >= WORLD_SIZE_X || (new_coords.y) < 0 || (new_coords.y) >= WORLD_SIZE_Y)
		throw ("Out of bounds"); // TODO: Proper error handling

	if (std::abs(this->coords.x-new_coords.x) + std::abs(this->coords.y-new_coords.y) == 0)
		throw ("Cannot stay on same field two turns in a row");

	if ((std::abs(this->coords.x-new_coords.x) + std::abs(this->coords.y-new_coords.y)) * 3 > this->fuel)
		throw ("Not enough fuel");

	if (this->game_world->getColumn(new_coords).empty())
		throw ("Cannot move to empty field");

	if (this->game_world->getSurfaceLayer()[new_coords.x][new_coords.y] != nullptr)
		throw ("Cannot move to occupied field");

	this->fuel -= (std::abs(this->coords.x-new_coords.x) + std::abs(this->coords.y-new_coords.y)) * 3;
	this->coords = this->game_world->moveBot(this, this->coords, new_coords);
}

void bot::extract() 
{
	if (this->defect) {
		this->defect = false;
		return;
	}

	if (this->ability != nullptr)
		this->ability->use({ this->coords.x, this->coords.y }, this->game_world);
	int extracted = this->drill->use({ this->coords.x, this->coords.y }, this->game_world);
	std::cout << "DEBUG bot.cpp:60 " << extracted << std::endl;
	this->score += extracted;
	int fuel = this->refinery->use(extracted);
	std::cout << "DEBUG bot.cpp:63 " << fuel << std::endl;
	this->fuel = std::min(this->fuel + fuel, this->max_fuel);

	if (this->score % REARRANGE == 0)
		this->game_world->rearrangeWorld();
}