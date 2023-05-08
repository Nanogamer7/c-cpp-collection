#include "display.h"

void display::displayStrings(std::vector<std::string> options)
{
    using namespace std;

    cout << options.at(0) << endl;
    for (int i = 1; i < options.size(); i++) {
        cout << " [" << to_string(i) << "] " << options.at(i) << endl;
    }
    cout << endl;
}

void display::displayStats(struct gameStats gameStats)
{
    using namespace std;

    cout << "+---------------------------------------------------------------------------------+" << endl;
    cout << "| " << lang::STR_MENU_STATS << setw(81 - lang::STR_MENU_STATS.length()) << " |" << endl;
    cout << "| " << "   " << setw(10) << gameStats.name_knight << ": " << setw(3) << gameStats.wins_knight << " " << lang::STR_GENERIC_WIN << ", " << setw(3) << gameStats.loses_knight << " " << lang::STR_GENERIC_LOSE << setw(49) << " |" << endl;
    cout << "| " << "   " << setw(10) << gameStats.name_hornet << ": " << setw(3) << gameStats.wins_hornet << " " << lang::STR_GENERIC_WIN << ", " << setw(3) << gameStats.loses_hornet << " " << lang::STR_GENERIC_LOSE << setw(49) << " |" << endl;
    cout << "| " << "   " << setw(10) << gameStats.name_custom << ": " << setw(3) << gameStats.wins_custom << " " << lang::STR_GENERIC_WIN << ", " << setw(3) << gameStats.loses_custom << " " << lang::STR_GENERIC_LOSE << setw(49) << " |" << endl;
    cout << "+---------------------------------------------------------------------------------+" << endl;
}

void display::displayPlayer(player* current, enemy* ally)
{
    using namespace std;

    cout << "+---------------------------------------------------------------------------------+" << endl;
    cout << "| " << lang::STR_MENU_CHAR << setw(81 - lang::STR_MENU_CHAR.length()) << " |" << endl;
    cout << "| " << "   " << current->strName() << setw(78 - (current->strName()).length()) << " |" << endl;
    cout << "| " << "   " << lang::STR_GENERIC_HEALTH << ": " << to_string(current->getHealth()) << setw(76 - (lang::STR_GENERIC_HEALTH.length() + to_string(current->getHealth()).length())) << " |" << endl;
    cout << "| " << "   " << lang::STR_GENERIC_STRENGTH << ": " << to_string(current->getStrength()) << setw(76 - (lang::STR_GENERIC_STRENGTH.length() + to_string(current->getStrength()).length())) << " |" << endl;
    cout << "| " << "   " << lang::STR_GENERIC_SOUL << ": " << to_string(current->getSoul()) << setw(76 - (lang::STR_GENERIC_SOUL.length() + to_string(current->getSoul()).length())) << " |" << endl;
    cout << "| " << "   " << lang::STR_GENERIC_SPEED << ": " << to_string(current->getSpeed()) << setw(76 - (lang::STR_GENERIC_SPEED.length() + to_string(current->getSpeed()).length())) << " |" << endl;
    if (current->getCharms().size() > 0)
        cout << "| " << lang::STR_MENU_CHARMS << setw(81 - lang::STR_MENU_CHARMS.length()) << " |" << endl;
    for (auto& charm : current->getCharms()) {
        cout << "| " << "   " << charm->getName() << setw(78 - (charm->getName()).length()) << " |" << endl;
    }
    if (ally != nullptr) {
        cout << "| " << lang::STR_MENU_YALLY << setw(81 - lang::STR_MENU_YALLY.length()) << " |" << endl;
        cout << "| " << "   " << ally->strName() << setw(78 - ally->strName().length()) << " |" << endl;
    }
    cout << "+---------------------------------------------------------------------------------+" << endl;
}

void display::displayOptionsMain()
{
    using namespace std;

    vector<string> options = {
        lang::STR_MENU_CHOICE_MAIN,
        lang::STR_MENU_FIGHT,
        lang::STR_MENU_SELF,
        lang::STR_MENU_ALLY,
        lang::STR_MENU_CHARM,
        lang::STR_MENU_CREATE,
        lang::STR_MENU_QUIT,
    };

    displayStrings(options);
}

void display::displayOptionsFight()
{
    using namespace std;

    vector<string> options = {
        lang::STR_MENU_CHOICE_FIGHT,
        lang::STR_MENU_FIGHT_SILK,
        lang::STR_MENU_FIGHT_INFEC,
        lang::STR_MENU_FIGHT_NIGHTMARE,
        lang::STR_MENU_BACK,
    };

    displayStrings(options);
}

void display::displayFightStats(std::vector<character *> allies, std::vector<character *> enemies) 
{
	std::cout << "+----------------------------------------+----------------------------------------+" << std::endl;
    std::cout << "|                 Allies                 |                Enemies                 |" << std::endl;
    std::cout << "+----------------------------------------+----------------------------------------+" << std::endl;

    // Display each ally and enemy's stats side-by-side
    for (std::size_t i = 0; i < std::max(allies.size(), enemies.size()); ++i) {
        std::string ally_name = i < allies.size() ? allies.at(i)->strName() : "";
        std::string ally_health = i < allies.size() ? allies.at(i)->strHealth() : "";
        std::string ally_strength = i < allies.size() ? (std::to_string(allies.at(i)->getStrength()) + " " + lang::STR_GENERIC_STRENGTH) : "";
        std::string ally_soul = i < allies.size() ? (allies.at(i)->getSoulMax() > 0 ? allies.at(i)->strSoul() : lang::STR_GENERIC_NO_SOUL) : "";
        std::string ally_speed = i < allies.size() ? (std::to_string(allies.at(i)->getSpeed()) + " " + lang::STR_GENERIC_SPEED) : "";
        
        std::string enemy_name = i < enemies.size() ? enemies.at(i)->strName() : "";
        std::string enemy_health = i < enemies.size() ? enemies.at(i)->strHealth() : "";
        std::string enemy_strength = i < enemies.size() ? (std::to_string(enemies.at(i)->getStrength()) + " " + lang::STR_GENERIC_STRENGTH) : "";
        std::string enemy_soul = i < enemies.size() ? (enemies.at(i)->getSoulMax() > 0 ? enemies.at(i)->strSoul() : lang::STR_GENERIC_NO_SOUL) : "";
        std::string enemy_speed = i < enemies.size() ? (std::to_string(enemies.at(i)->getSpeed()) + " " + lang::STR_GENERIC_SPEED) : "";
        
        std::cout << "| "<< std::left << ally_name << std::setw((int) (38 - ally_name.length())) << std::right << ally_health << " | ";
        std::cout << std::left << enemy_name << std::setw((int) (38 - enemy_name.length())) << std::right << enemy_health << " |" << std::endl;
        std::cout << "| " << std::setw(38) << std::right << ally_strength << " | " << std::setw(38) << std::right << enemy_strength << " |" << std::endl;
        std::cout << "| " << std::setw(38) << std::right << ally_soul << " | " << std::setw(38) << std::right << enemy_soul << " |" << std::endl;
        std::cout << "| " << std::setw(38) << std::right << ally_speed << " | " << std::setw(38) << std::right << enemy_speed << " |" << std::endl;

    	std::cout << "+----------------------------------------+----------------------------------------+" << std::endl;
    }
    std::cout << std::endl;
}