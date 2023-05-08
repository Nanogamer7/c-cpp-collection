#include "grub.h"

grub::~grub() {}

int grub::defMod(int damage, dmg_type type, character* source, character* target) 
{
	target->useSoul(this->soul * (-1));
	return damage;
}