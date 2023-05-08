#include "_main_header.h"
int main()
{
    srand(time(0));
    bool alive = true;

    struct gameStats gameStats = { 0, "The Knight", "Hornet", "Vessel", 0,0,0,0,0,0};

    player* current = nullptr;
    enemy* ally = nullptr;

    std::vector<player*> playable = {
        createChar<player>(the_knight),
        nullptr,
    };

    std::vector<enemy*> allies = {
        createChar<enemy>(quirrel), // memory leak
        createChar<enemy>(zote), // memory leak
    };

    while (true) { // main loop
        int choice;

        display::displayStats(gameStats);
        if (current != nullptr)
            display::displayPlayer(current, ally);

        std::cout << std::endl;
        display::displayOptionsMain();
        std::cin >> choice;
        choice %= 6;

        if (choice == 0) // to avoid a goto
            break;

        std::vector<std::string> options = { // out here cause weird error
            lang::STR_MENU_CHOICE_CHAR,
        };
        for ( auto& current : playable ) {
            if (current != nullptr)
                options.push_back(current->strName());
        }
        std::vector<std::string> allies_str = { lang::STR_MENU_CHOICE_ALLY };

        for ( auto& ally : allies ) {
            allies_str.push_back(ally->strName());
        }
        allies_str.push_back(lang::STR_MENU_BACK);

        switch (choice) {
        case 1:
            if (current == nullptr) {
                current = playable.front();
                gameStats.selected = 1;
            }


            display::displayOptionsFight();
            std::cin >> choice;
            choice--;
            choice %= 4;
            if (choice != 4) {
                int win = startFight(current, ally, static_cast<enum fight_type>(choice));
                if (win == -1)
                    break;;
                gameStats = outcomeHandler(gameStats, win); // leak
                if (win && choice == 0) {
                    playable.push_back(createChar<player>(hornet_friend));
                    allies.push_back(createChar<enemy>(hornet_friend));
                }
            }
            break;
        case 2:
            display::displayStrings(options);
            std::cin >> choice;
            current = playable.at((choice - 1) % playable.size());
            gameStats.selected = choice % playable.size();
            break;

        case 3:
            display::displayStrings(allies_str);
            std::cin >> choice;
            choice %= allies_str.size() - 1;
            if (choice == 0)
                break;
            choice--;
            ally = allies.at(choice);
            break;

        case 4:
            if (current == nullptr) {
                std::cout << lang::STR_MENU_ERR_CHAR << std::endl;
                break;
            }
            selectCharms(current);
            break;

        case 5:
            playable.at(1) = customChar(playable.at(1));
            current = playable.at(1);
            gameStats.selected = 3;
            break;

        }
    }

    for ( auto& character : playable ) {
        (character != nullptr) ? delete character : void();
    }

    for ( auto& ally : allies ) {
        (ally != nullptr) ? delete ally : void();
    }
    
    return 0;
}

template <typename bug>
bug* createChar(enum char_type type)
{
    bug* newChar = nullptr;
    switch (type)
    {
    case the_knight:
        newChar = new bug("The Knight", 120, 20, 100, 15);
        newChar->addMove(new class nail(100, 11, nail));
        newChar->addMove(new class fireball(35, 33, fireball));
        newChar->addMove(new class focus(40, 33));
        // no tree since won't be an enemy
        break;
    case hornet_friend:
        newChar = new bug("Hornet", 100, 12, 0, 25);
        newChar->addMove(new class nail(150, 0, (enum nail_type) needle));
        newChar->addMove(new class dash(80, 50, 0, lunge));
        newChar->addMove(new class parry());
        newChar->setTree(new class treeBrain());
        break;
    case hornet_enemy:
        newChar = new bug("Hornet", 150, 20, 0, 25);
        newChar->addMove(new class nail(150, 0, (enum nail_type) needle));
        newChar->addMove(new class needle(100, (enum needle_type) needle_throw));
        newChar->addMove(new class dash(35, 35, 0, lunge));
        newChar->setTree(new class treeBrain());
        break;
    case quirrel:
        newChar = new bug("Quirrel", 100, 20, 0, 10);
        newChar->addMove(new class nail(100, 11, nail));
        newChar->addMove(new class dash(75, 40, 0, lunge));
        newChar->setTree(new class treeBrain());
        break;
    case zote:
        newChar = new bug("Zote", 120, 10, 0, 15);
        newChar->addMove(new class nail(100, 0, nail));
        newChar->setTree(new class treeDumb());
        break;
    case mantis:
        newChar = new bug("Mantislord", 90, 30, 0, 15);
        newChar->addMove(new class needle(100, blades));
        newChar->addMove(new class dash(50, 33, 0, lance));
        newChar->setTree(new class treeBrain());
        break;
    case broken_vessel:
        newChar = new bug("Broken Vessel", 100, 20, 100, 5);
        newChar->addMove(new class dash(50, 0, 50, slash));
        newChar->addMove(new class aoe(60, 100, cascade));
        newChar->setTree(new class treeBrain());
        break;
    case god_tamer:
        newChar = new bug("God Tamer", 70, 15, 0, 20);
        newChar->addMove(new class dash(100, 50, 50, lunge));
        newChar->setTree(new class treeGreed());
        break;
    case beast:
        newChar = new bug("Beast", 250, 30, 100, 10);
        newChar->addMove(new class dash(33, 75, 100, roll));
        newChar->addMove(new class aoe(20, 33, spew));
        newChar->setTree(new class treeDumb());
        break;
    case hollow_knight:
        newChar = new bug("Hollow Knight", 200, 25, 100, 10);
        newChar->addMove(new class nail(100, 15, nail));
        newChar->addMove(new class dash(70, 40, 15, lunge));
        newChar->addMove(new class aoe(40, 60, spew));
        newChar->setTree(new class treeBrain());
        break;
    case troupe_grimm:
        newChar = new bug("Troupe Master Grimm", 175, 30, 100, 10);
        newChar->addMove(new class dash(75, 40, 11, dive));
        newChar->addMove(new class dash(75, 40, 11, uppercut));
        newChar->addMove(new class fireball(30, 33, bats));
        newChar->setTree(new class treeBrain());
        break;
    case nightmare:
        newChar = new bug("Nightmare King Grimm", 225, 50, 100, 20);
        newChar->addMove(new class dash(75, 30, 11, dive));
        newChar->addMove(new class dash(75, 30, 11, uppercut));
        newChar->addMove(new class fireball(40, 33, bats));
        newChar->setTree(new class treeBrain());
        break;
    }

    return newChar;
}

player* customChar(player* newChar)
{
    int selection;

    if (newChar != nullptr) {
        std::vector<std::string> strings = {
            lang::STR_MENU_CHAR_WARNING,
            lang::STR_MENU_CONTINUE,
            lang::STR_MENU_CANCEL,
        };

        display::displayStrings(strings);
        std::cin >> selection;
        if (selection == 1)
            return newChar;
        newChar = nullptr;
    }

    int itemp;

    std::vector<move*> moves = {
        new class nail(100, 11, nail),
        new class cloak(100),
        new class fireball(35, 33, fireball),
        new class dive(30, 50),
        new class focus(40, 33),
    };

    struct charStats playerStats = { 80, 10, 0, 5 };

    std::vector<move*> equipped;

    while (equipped.size() < MAX_MOVES) {
        itemp = -1;

        std::vector<std::string> options = { lang::STR_MENU_CHOICE_MOVE };
        for (auto& move : moves) {
            options.push_back(move->getName());
        }
        options.push_back(lang::STR_MENU_CANCEL);

        std::cout << "+---------------------------------------------------------------------------------+" << std::endl << std::endl;
        display::displayStrings(options);
        std::cin >> selection;
        selection--;
        selection %= options.size();

        if (selection == options.size() - 2)
            goto cleanup;

        move* temp = moves.at(selection);
        itemp = selection;

        std::cout << "+---------------------------------------------------------------------------------+" << std::endl << std::endl;
        std::cout << moves.at(selection)->getName() << std::endl;
        std::cout << moves.at(selection)->getDescr() << std::endl;

        display::displayStrings({ "", lang::STR_MENU_EQUIP, lang::STR_MENU_BACK });
        std::cin >> selection;

        if (selection == 2)
            continue;

        if (equipped.size() < MAX_MOVES) {
            equipped.push_back(temp);
            moves.erase(moves.begin() + itemp);
            continue;
        }

        std::cout << "+---------------------------------------------------------------------------------+" << std::endl << std::endl;
        options = { lang::STR_MENU_CHOICE_MOVE_REPLACE };
        for (auto& move : equipped) {
            options.push_back(move->getName());
        }
        options.push_back(lang::STR_MENU_CANCEL);
        display::displayStrings(options);
        std::cin >> selection;
        if (selection == MAX_MOVES + 1)
            continue;
        equipped.at((selection-1) % MAX_MOVES) = temp;
        moves.erase(moves.begin() + itemp);
    }

    for ( auto& move : equipped ) {
        if (move->getCost() < 0) {
            playerStats.soul = 50;
            break;
        }
    }

    newChar = new player("Vessel", playerStats.health, playerStats.strength, playerStats.soul, playerStats.speed);

    for (int i = 0; i < STAT_POINTS; i++) {
        display::displayPlayer(newChar, nullptr);
        std::cout << "debug: " << newChar->strName() << std::endl;
        delete newChar;

        std::cout << "+---------------------------------------------------------------------------------+" << std::endl << std::endl;
        std::cout << lang::STR_MENU_AVAIL_POINTS << std::to_string(STAT_POINTS - i) << std::endl;
        std::vector<std::string> options = {
            lang::STR_MENU_CHOICE_CHARM_REPLACE,
            lang::STR_MENU_INCR_HEALTH + std::to_string(PLUS_HEALTH),
            lang::STR_MENU_INCR_STRENGTH + std::to_string(PLUS_STRENGTH),
            lang::STR_MENU_INCR_SOUL + std::to_string(PLUS_SOUL),
            lang::STR_MENU_INCR_SPEED + std::to_string(PLUS_SPEED),
        };

        display::displayStrings(options);
        std::cin >> selection;

        switch (selection) {
        case 1:
            playerStats.health += PLUS_HEALTH;
            break;
        case 2:
            playerStats.strength += PLUS_STRENGTH;
            break;
        case 3:
            playerStats.soul += PLUS_SOUL;
            break;
        case 4:
            playerStats.speed += PLUS_SPEED;
            break;
        }

        newChar = new player("Vessel", playerStats.health, playerStats.strength, playerStats.soul, playerStats.speed);
    }

    for ( auto& move : equipped ) // ugly af code
        newChar->addMove(move);

    for ( auto& move : moves) {
        delete move;
    }
    return newChar;

    cleanup: 
    
    for ( auto& move : equipped) {
        delete move;
    }
    for ( auto& move : moves) {
        delete move;
    }
    return newChar;
}

player* playerSelect(player* newChar)
{
    int choice = 0;
    std::cout << "Select a character:\n [1] The Knight\n [2] Hornet\n [3] Create Vessel" << std::endl; // TODO: this is stupid
    std::cin >> choice;
    choice--;
    choice %= 3;


    if (choice == 3) {
        return customChar(newChar);
    }

    enum char_type type = static_cast<enum char_type>(choice);
    return createChar<player>(type);
}

void selectCharms(player* newChar)
{
    int selection;
    int itemp;

    std::vector<charm*> charms = {
        new class baldur(150),
        new class fury(70),
        new class grub(11),
        new class strength(8),
        new class thorns(10),
        new class twister(13),
    };

    while (true) {
        itemp = -1;

        std::vector<std::string> options = { lang::STR_MENU_CHOICE_CHARM };
        for (auto& charm : charms) {
            options.push_back(charm->getName());
        }
        options.push_back(lang::STR_MENU_BACK);

        std::cout << "+---------------------------------------------------------------------------------+" << std::endl << std::endl;
        display::displayStrings(options);
        std::cin >> selection;
        selection--;
        selection %= options.size();

        if (selection == options.size() - 2)
            break;

        charm* temp = charms.at(selection);
        itemp = selection;

        std::cout << "+---------------------------------------------------------------------------------+" << std::endl << std::endl;
        std::cout << charms.at(selection)->getName() << std::endl;
        std::cout << charms.at(selection)->getDescr() << std::endl;

        display::displayStrings({ "", lang::STR_MENU_EQUIP, lang::STR_MENU_BACK });
        std::cin >> selection;

        if (selection == 2)
            continue;

        if (newChar->charmsAmount() < MAX_CHARMS) {
            newChar->addCharm(temp);
            break;
        }

        std::cout << "+---------------------------------------------------------------------------------+" << std::endl << std::endl;
        options = { lang::STR_MENU_CHOICE_CHARM_REPLACE };
        for (auto& equipped : newChar->getCharms()) {
            options.push_back(equipped->getName());
        }
        options.push_back(lang::STR_MENU_CANCEL);
        display::displayStrings(options);
        std::cin >> selection;
        if (selection == MAX_CHARMS + 1)
            continue;
        newChar->replaceCharm(temp, (selection-1) % MAX_CHARMS);
        break;
    }

    if (itemp >= 0)
        charms.erase(charms.begin() + itemp);
    for ( auto& charm : charms) {
        delete charm;
    }

}
bool fight(team* ally_team, std::vector<enum char_type> enemies)
{
    bool win;
    team* enemy_team = nullptr;
    arena* arena = nullptr;

    enemy_team = new class team();
    for ( auto& enemy_type : enemies) {
        enemy_team->addMember(createChar<enemy>(enemy_type));
    }

    arena = new class arena(ally_team, enemy_team);
    win = arena->fight();
    
    enemy_team->deleteMembers();
    delete enemy_team;

    delete arena;
    return win;
}

int startFight(player* current, enemy* ally, enum fight_type fight_type)
{
    std::vector<enum char_type> enemies;
    std::vector<std::vector<enum char_type>> fights;

    team* ally_team = new class team();
    ally_team->addMember(current);
    if (ally != nullptr)
        ally_team->addMember(ally);

    switch (fight_type) {
    case easy:

        fights.push_back({ hornet_enemy });
        fights.push_back({ mantis, mantis });
        break;

    case hard:

        fights = {{ broken_vessel }, { god_tamer, beast }, { hollow_knight }};
        break;

    case impossible:

        fights = {{ troupe_grimm }, {nightmare}};
        break;

    default:
        delete ally_team;
        return -1;
    }

    bool win;
    for ( auto& fight : fights ){
        win = ::fight(ally_team, fight);
        if (win == false)
            break;
    }

    delete ally_team;
    current->reset();
    return win;
}

struct gameStats outcomeHandler(gameStats gs, bool win) {
    switch(gs.selected) {
        case 1:
            win ? gs.wins_knight++ : gs.loses_knight++;
            break;
        case 2:
            win ? gs.wins_hornet++ : gs.loses_hornet++;
            break;
        case 3:
            win ? gs.wins_custom++ : gs.loses_custom++;
            break;
        default:
            break;
    }
    return gs;
}
