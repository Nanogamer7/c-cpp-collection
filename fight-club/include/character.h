#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

class charm;
class move;
class team;

#define MAX_MOVES 3
#define MAX_CHARMS 2
#define PSEUDO_CHARM 1


enum attribute { hp, stren, mana, spd };

enum dmg_type {
    melee,
    ranged,
    proc,
    heal,
};

class character
{
    public:

        character(std::string name, int health, int strength, int soul, int speed);
        virtual ~character();

        virtual std::string strName() const;
        std::string strHealth() const;
        std::string strSoul() const;

        void printDodge() const;

        int getHealth() const { return this->health; };
        int getHealthMax() const { return this->max_health; };
        int getSoul() const { return this->soul; };
        int getSoulMax() const { return this->max_soul; };
        int getStrength() const { return this->strength + this->strength_mod > 0 ? this->strength + this->strength_mod : 0; };
        int getStrengthBase() const { return this->strength; };
        int getSpeed() const { return this->speed + this->speed_mod > 0 ? this->speed + this->speed_mod : 0; };

        void modStrength(int strength) { this->strength_mod += strength; };
        void modSpeed(int speed) { this->speed_mod += speed; };

        bool takeDamage(int damage, enum dmg_type type, character* source); // TODO: damage types
        bool doDamage(int damage, enum dmg_type type, character* target); // TODO: damage types
        bool useSoul(int soul);

        void turnStart();
        void action();
        virtual void decision() = 0;
        void setTree(class decision* tree) { this->tree = tree; }; // in parent class since it doesn't affect other child classes
        void win();
        void reset();

        bool addCharm(charm* charm);
        bool addMove(move* move);

        int charmsAmount() { return this->charms.size(); };
        void replaceCharm(charm* newCharm, int pos) { this->charms.at(pos) = newCharm; };
        std::vector<charm*> getCharms() { return charms; };

        int movesAmount() { return this->moves.size(); };
        void replaceMove(move* newMove, int pos) { this->moves.at(pos) = newMove; };
        std::vector<move*> getMoves() { return moves; };

        void setTeam(team* team) { this->allied_team = team; };
        team* getTeam() { return this->allied_team; };

    protected:

        std::string name;
        int health;
        int max_health;

        int strength;
        int strength_mod;

        int soul;
        int max_soul;

        int speed;
        int speed_mod;

        // Overload greater than operator to sort team->members by speed
        bool operator<(const character& x) const {
            return this->getSpeed() < x.getSpeed();

        }

        // Overload less than operator to sort team->members by health
        bool operator>(const character& x) const {
            return this->getHealth() > x.getHealth();
        }

        std::vector<move*> moves;
        std::vector<charm*> charms;

        team* allied_team;

        class decision* tree = nullptr;

    private:

        virtual void death() = 0;
};

#endif // CHARACTER_H
