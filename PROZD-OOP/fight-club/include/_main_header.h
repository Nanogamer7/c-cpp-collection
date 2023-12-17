#include <cstdlib>
#include <ctime>
#include <iterator>

#include "arena.h"

// moves and charms
#include "aoe.h"
#include "baldur.h"
#include "cloak.h"
#include "dash.h"
#include "fury.h"
#include "grub.h"
#include "nail.h"
#include "needle.h"
#include "strength.h"
#include "fireball.h"
#include "focus.h"
#include "nail.h"
#include "thorns.h"
#include "parry.h"
#include "aoe.h"
#include "twister.h"
#include "dive.h"

// decision trees
#include "treeGreed.h"
#include "treeDumb.h"
#include "treeBrain.h"

// display functions
#include "display.h"

#define STAT_POINTS 8
#define PLUS_HEALTH 20
#define PLUS_STRENGTH 5
#define PLUS_SOUL 25
#define PLUS_SPEED 5

enum char_type {
    the_knight, hornet_friend, hornet_enemy, quirrel, zote, mantis, broken_vessel, god_tamer, beast, hollow_knight, troupe_grimm, nightmare,
};

enum fight_type {
    easy, hard, impossible
};

struct charStats {
    int health;
    int strength;
    int soul;
    int speed;
};

template <typename bug>
bug* createChar(enum char_type type);

player* customChar(player* newChar);
void selectCharms(player* player);
player* playerSelect(player* newChar);

bool fight(team* ally_team, std::vector<enum char_type> enemies);
int startFight(player* player, enemy* ally, enum fight_type fight_type);
struct gameStats outcomeHandler(struct gameStats gameStats, bool win);