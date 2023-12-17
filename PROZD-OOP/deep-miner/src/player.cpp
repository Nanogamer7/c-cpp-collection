#include "player.h"

player::~player() {}

void player::makeMove() 
{
	using namespace std;

	struct coords move;
	std::string in; // assuming single character coordinates

	while (true) {
		cout << "Choose a field to move to: ";
		cin >> in;

		move.x = in[1] - '1';
		move.y = in[0] - 'A';
		try {
			this->move(move);
		} catch (char const* error) {
			cout << error << endl;
			continue;
		}
		std::cout << "DEBUG player.cpp:26 success" << std::endl;
		break;
	}

	cout << endl;

}