#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define WORLD_SIZE_X 5
#define WORLD_SIZE_Y 5
#define WORLD_SIZE_Z 9

#define MOVE_COST 2

#define REARRANGE 50

enum world_action {
	shuffle,
	sort_desc,
	sort_asc,
};

enum menu_opt {
	pve = 1,
	eve,
	quit,
};

enum bot_type {
	deep = 1,
	pump,
	filter,
};

enum trap_type {
	defect = 1,
	landslide,
	leak,
};

struct coords {
	int x;
	int y;
};

struct field_stats {
	struct coords coords;
	int distance;
	int value;

	bool operator>(const field_stats& other) const {
		return value - distance > other.value - other.distance ? true : 
			value - distance == other.value - other.distance ? value > other.value : false;
	}
};

#endif