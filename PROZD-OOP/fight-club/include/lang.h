#ifndef LANG_H
#define LANG_H

#include "character.h"

namespace lang {

	using std::string;

	static const string STR_MOVE_NAIL_NAME[2] = { // nail.h
		"Sharpened Nail",
		"Needle",
	};
	static const string STR_MOVE_NAIL_DESCR[2] = {
		"Hit bugs. It's just a nail, what did you expect?",
		"An elegant weapon only for the most skillful bugs.",
	};
	static const string STR_MOVE_FOCUS_NAME = "Focus"; // focus.h
	static const string STR_MOVE_FOCUS_DESCR = "Focus soul to heal";
	static const string STR_MOVE_NTHROW_NAME[2] = { // needle.h
		"Needle Throw",
		"Bladed Boomerang",
	};
	static const string STR_MOVE_NTHROW_DESCR[2] = {
		"Your needle is on a thread for a reason",
		"",
	};
	static const string STR_MOVE_PARRY_NAME = "Parry"; // parry.h
	static const string STR_MOVE_PARRY_DESCR = "Parry the next attack";
	static const string STR_MOVE_CLOAK_NAME = "Mothwing Cloak"; // cloak.h
	static const string STR_MOVE_CLOAK_DESCR = "It's just a dash";
	static const string STR_MOVE_FIREBALL_NAME[2] = { // fireball.h
		"Vengeful Spirit",
		"Fire Bats",
	};
	static const string STR_MOVE_FIREBALL_DESCR[2] = {
		"Shoot a powerful fireball",
		"",
	};
	static const string STR_MOVE_DIVE_NAME = "Desolate Dive"; // dive.h
	static const string STR_MOVE_DIVE_DESCR = "Dive to the ground with a concentrated force of Soul. Short invulnerability";
	static const string STR_MOVE_DASH_NAME[6] = { // dash.h
		"Lunge",
		"Lance Dash",
		"Roll",
		"Slash",
		"Dive Dash",
		"Uppercut",
	};
	static const string STR_MOVE_DASH_DESCR[6] = {
		"Lunge at your opponent",
		"", "", "", "", "",
	};
	static const string STR_MOVE_AOE_NAME[2] = { // aoe.h
		"Spew",
		"Cascade",
	};
	static const string STR_MOVE_AOE_DESCR = { // aoe.h
		"", "",
	};

	static const string STR_MOVE_LOON_NAME = "Balloon"; // balloon.h
	static const string STR_MOVE_LOON_DESCR = "";

	static const string STR_CHARM_THORNS_NAME = "Thorns of Agony";
	static const string STR_CHARM_THORNS_DESCR = "Damages nearby enemies when getting hit";
	static const string STR_CHARM_TWISTER_NAME = "Spell Twister";
	static const string STR_CHARM_TWISTER_DESCR = "Reduces Soul cost when casting spells";
	static const string STR_CHARM_STRENGTH_NAME = "Unbreakable Strength";
	static const string STR_CHARM_STRENGTH_DESCR = "Strengthens the bearer, increasing the damage they deal to enemies";
	static const string STR_CHARM_BALDUR_NAME = "Baldur Shell";
	static const string STR_CHARM_BALDUR_DESCR = "Protects its bearer with a hard shell while focusing";
	static const string STR_CHARM_GRUBS_NAME = "Grubsong";
	static const string STR_CHARM_GRUBS_DESCR = "Gain Soul when taking damage";
	static const string STR_CHARM_FURY_NAME = "Fury of the Fallen";
	static const string STR_CHARM_FURY_DESCR = "When close to death, the bearer's strength will increase";



	static const string STR_GENERIC_UNAVAILABLE = "Unavailable"; // spaces after words depending on use
	static const string STR_GENERIC_SOUL = "soul";
	static const string STR_GENERIC_STRENGTH = "strength";
	static const string STR_GENERIC_HEALTH = "health";
	static const string STR_GENERIC_SHIELD = "shield";
	static const string STR_GENERIC_SPEED = "speed";
	static const string STR_GENERIC_DEAD = "dead";
	static const string STR_GENERIC_DIE = "died";
	static const string STR_GENERIC_YOU = "you";
	static const string STR_GENERIC_WIN = "won";
	static const string STR_GENERIC_LOSE = "lost";
	static const string STR_GENERIC_YOUC_ = "You ";
	static const string STR_GENERIC_LOCK = "locked";
	static const string STR_GENERIC_NO_SOUL = "no soul";
	static const string STR_GENERIC_USE_ = "used ";
	static const string STR_GENERIC_RECEIVE_ = "received ";
	static const string STR_GENERIC_DODGE = "dodged the attack";
	static const string STR_GENERIC_DEAL_ = "It dealt ";
	static const string STR_GENERIC_AND_DEAL_ = "and dealt ";
	static const string STR_GENERIC__DMG = " damage";
	static const string STR_GENERIC_MISS = "It missed.";
	static const string STR_GENERIC_HEAL_ = "It healed by ";
	static const string STR_GENERIC__PROC_ = " activated ";
	static const string STR_GENERIC__PARRY_ = " parried ";
	static const string STR_GENERIC_SATACK_ = " 's attack";
	static const string STR_GENERIC_ = "";



	static const string STR_COMBAT_CHOICE_MOVE = "Choose a move: ";
	static const string STR_COMBAT_CHOICE_TARGET = "Choose a target: ";
	static const string STR_COMBAT_CURRENT_HEALTH = "Your current health: ";
	static const string STR_COMBAT_ENTER_CONTINUE = "Press enter to continue...";

	static const string STR_MENU_CHOICE_MAIN = "Choose what to do: ";
	static const string STR_MENU_CHOICE_FIGHT = "Choose a fight: ";
	static const string STR_MENU_CHOICE_CHAR = "Select a character: ";
	static const string STR_MENU_CHOICE_CHARM = "Select a charm to equip. You can equip up to " + std::to_string(MAX_CHARMS) + " charms: ";
	static const string STR_MENU_CHOICE_MOVE = "Select a move. You can have up to " + std::to_string(MAX_MOVES) + " moves:  ";
	static const string STR_MENU_CHOICE_STAT = "Select a stat to increase: ";
	static const string STR_MENU_CHOICE_ALLY = "Select an ally. Allies will help you in combat: ";
	static const string STR_MENU_CHAR_WARNING = "Warning! Creating a new Vessel will overrite your old one. Continue?";
	static const string STR_MENU_QUIT = "Quit the game";
	static const string STR_MENU_FIGHT = "Fight";
	static const string STR_MENU_CHARM = "Equip charms";
	static const string STR_MENU_CREATE = "Create or modify your Vessel";
	static const string STR_MENU_SELF = "Choose your character";
	static const string STR_MENU_ALLY = "Choose an ally";
	static const string STR_MENU_FIGHT_SILK = "Silksong";
	static const string STR_MENU_FIGHT_INFEC = "Hallownest";
	static const string STR_MENU_FIGHT_NIGHTMARE = "The Nightmare";
	static const string STR_MENU_STATS = "Fights won & lost today: ";
	static const string STR_MENU_CHAR = "Your selected character: ";
	static const string STR_MENU_CONTINUE = "Continue";
	static const string STR_MENU_BACK = "Go back";
	static const string STR_MENU_CANCEL = "Cancel";
	static const string STR_MENU_CHOICE_CHARM_REPLACE = "Select a charm to replace: ";
	static const string STR_MENU_CHOICE_MOVE_REPLACE = "Select a move to replace: ";
	static const string STR_MENU_EQUIP = "Equip";
	static const string STR_MENU_ERR_CHAR = "Select a character first!";
	static const string STR_MENU_CHARMS = "Equiped charms: ";
	static const string STR_MENU_YALLY = "Your ally: ";

	static const string STR_MENU_INCR_HEALTH = "Increase " + STR_GENERIC_HEALTH + " by ";
	static const string STR_MENU_INCR_SOUL = "Increase " + STR_GENERIC_SOUL + " by ";
	static const string STR_MENU_INCR_STRENGTH = "Increase " + STR_GENERIC_STRENGTH + " by ";
	static const string STR_MENU_INCR_SPEED = "Increase " + STR_GENERIC_SPEED + " by ";
	static const string STR_MENU_AVAIL_POINTS = "Available stat increases: ";

}

#endif // LANG_H