#include "Board.hpp"

using namespace std;

bool	input(int &x) {
	string s; getline(cin, s);
	try {
		x = stoi(s);
	} catch(std::exception& e) {
		x = 0;
	}
	if ((x >= 1 && x <= 7))
		return true;
	cerr << RED << "Invalid inputs\n" << RESET;
	return false;
}

int		main()
{
	int x = 0, turn = 1;
	bool ret;
	Board b;

	cout << b;
	while (cin.eof() != true) {
		cout << "Please input number (1 ~ 7) " << endl;
		cout << "Player" << (turn == 1 ? turn : 2) << ": ";
		if ((ret = input(x))) {
			if (b.Reflect_Input(x, turn) == false) {
				cerr << RED << "Not Empty\n" << RESET;
				ret = false;
			}
		}
		cout << b;
		if (b.ValidateBoard(x, turn)) {
			cout << "Winner: Player" << (turn == 1 ? turn : 2) << endl;
			return 0;
		}
		if (ret)
			turn *= -1;
	}
	return 0;
}
