#include <ctime>

#include "display.h"
#include "game.h"
#include "player.h"
#include "computer.h"
#include "pump.h"
#include "filter.h"

void menu();
void newGame(enum menu_opt opt);
bot_type botSel();
bot* botCreate(enum bot_type type, bool player);

int main()
{
    srand(time(NULL));
    menu();
}

void menu()
{
    while (true) {
        display::mainMenu();
        while (true) {
            int input;
            std::cin >> input;
            enum menu_opt opt = static_cast<enum menu_opt>(input);
            try {
                switch (opt) {
                    case pve:
                    case eve:
                        newGame(opt);
                        break;
                    case quit:
                        return;
                    default:
                        throw "Invalid input, try again!";
                    }
            } catch (char const* error) {
                std::cout << error << std::endl;
                continue;
            }
            break;
        }
    }
}

void newGame(enum menu_opt opt)
{
    game* game = new class game();

    opt == pve ? game->addBot(botCreate(botSel(), true)) : game->addBot(botCreate(botSel(), false));
    game->addBot(botCreate(botSel(), false));

    game->startGame();

    std::cout << game->getWinner()->getName() << " won the round with " << game->getWinner()->getScore() << " points!" << std::endl;

    delete game;

}

bot_type botSel()
{
    enum bot_type bot;
    while (true) {
        try {
            int select;
            display::botSelector();
            std::cin >> select;
            bot = static_cast<enum bot_type>(select);
            switch (bot) {
                case deep:
                case pump:
                case filter:
                    break;
                default:
                    throw "Invalid input, try again!";
                }

        } catch (char const* error) {
            std::cout << error << std::endl;
            continue;
        }
        break;
    }

    return bot;
}

bot* botCreate(enum bot_type type, bool player)
{
    int fuel;
    char A = (char) 'A' + rand()%26;
    std::string name = std::string(1, A) + std::to_string(rand()%90 + 10);
    refinery* refinery;
    drill* drill;
    ability* ability;

    switch (type) {
        case deep:
            fuel = 30;
            refinery = new class refinery(75);
            drill = new class drill(2);
            ability = nullptr;
            break;
        case pump:
            fuel = 30;
            refinery = new class refinery(90);
            drill = new class drill(1);
            ability = new class pump();
            break;
        case filter:
            fuel = 30;
            refinery = new class refinery(100);
            drill = new class drill(1);
            ability = new class filter();
            break;
    }

    bot* bot;
    if (player) {
        bot = new class player(fuel, name, refinery, drill, ability);
    } else {
        bot = new class computer(fuel, name, refinery, drill, ability);
    }

    return bot;
}