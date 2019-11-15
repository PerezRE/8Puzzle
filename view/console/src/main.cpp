#include <iostream>
#include <string.h>
#include "../../../controllers/Game.hpp"

using namespace std;

int menu();
char** ask_board(const int&);

int main(int argc, char* argv[]) {
	const int SIZE = 3;

	cout << "Start" << endl;
	char** start = ask_board(SIZE);
	cout << "Goal" << endl;
	char** goal = ask_board(SIZE);
	Game* game = new Game(SIZE, start, goal);

	int op;
	while (!game->game_over()) {
		system("CLS");
		cout << *game << endl;
		op = menu();
		switch (op)
		{
			case 4:
				game->move_left();
				break;
			case 8:
				game->move_up();
				break;
			case 6:
				game->move_right();
				break;
			case 2:
				game->move_down();
				break;
			case 7:
				game->resolve();
				break;
			case 0:
				game->set_target(SIZE, ask_board(SIZE));
				break;
			case 1:
				delete game;
				exit(0);
				break;
			default:
				cout << "Invalid option, try again." << endl;
				system("PAUSE");
				break;
		}
	}
	delete game;
	return 0;
}

int menu() {
	int op;
	cout << "[4] Move left" << endl
		<< "[8] Move up" << endl
		<< "[6] Move right" << endl
		<< "[2] Move down" << endl
		<< "[7] Resolve" << endl
		<< "[0] Change goal state" << endl
		<< "[1] Exit" << endl
		<< "Option: ";
	cin >> op;
	return op;
}

char** ask_board(const int &size) {
	char* row = new char[size];
	char** goal = new char* [size];
	for (int i = 0; i < size; i++) {
		cout << "Please type the row " << "[" << i + 1 << "]" << " of " << size << " elements" << " (example 104): ";
		cin >> row;
		if (strlen(row) == 3) {
			goal[i] = new char[size];
			for (int j = 0; j < size; j++)
				goal[i][j] = row[j];
		}
		else {
			cout << "Input must a value with " << size << " elements" << endl;
			i--;
		}
	}
	delete[] row;
	return goal;
}