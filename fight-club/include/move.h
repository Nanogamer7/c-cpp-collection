#ifndef MOVE_H
#define MOVE_H

#include "team.h"
#include "lang.h"

enum move_type {
	targeted,
	area,
	self,
};

class move
{
	public:

		virtual ~move();
		virtual bool use(character* source, character* target) = 0;

		virtual std::string getName() const { return name; };
		virtual std::string getDescr() const { return descr; };
		int					getCost() const { return cost; };
		int					getDamage() const { return damage; };
		int					getSoul() const { return soul; };
		int					getSpeed() const { return speed; };
		bool				getParry() const { return is_parry; };
		enum move_type		getType() const { return type; };

	protected:

		std::string name;
		std::string descr;
		
		int damage = -1;
		int cost = -1;
		int soul = -1;
        int speed = -1;
        bool is_parry = false;
		enum move_type type;

        bool operator<(const move& x) const {
            return this->getDamage() < x.getDamage();
        };

};

#endif // MOVE_H
