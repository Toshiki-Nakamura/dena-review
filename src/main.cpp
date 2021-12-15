#include <vector>
#include <iostream>
#include <string>

using namespace std;

#define WIDTH 7
#define HEIGHT 6
#define Empty '.'

vector<string> grid(7, "*******");

class Board {
private:
	vector<string> _grid;
	int			Y;
public: 
	Board() : _grid(7, string(7, Empty)) {_grid[6] = string(7, '_');}
	~Board() {}
	void	Reflect_Input(int x, int turn) {
		x--;
		if (_grid[0][x] != Empty)
			return ;
		for (size_t i = 0; i < HEIGHT; i++) {
			if (_grid[i+1][x] != Empty) {
				if (turn < 0) _grid[i][x] = 'x';
				else  _grid[i][x] = 'o';
				Y = i;
				return ;
			}
		}
	}
	// とりあえずタテ・ヨコ判定まで
	bool	ValidateBoard(int x, int turn) {
		string search = turn < 0 ? "xxxx" : "oooo";
		if (_grid[Y].find(search) != string::npos) {
			return true;
		}
		string row;
		for (size_t i = 0; i < WIDTH; i++)
			row.push_back(_grid[i][x-1]);
		cout << "row: " << row << endl;
		cout << "x: " << x << endl;
		cout << "search: " << search << endl;
		if (row.find(search) != string::npos) {
			return true;
		}
		return false;
	}
	std::string const &operator[](int index) const {return _grid[index];}
	std::string &operator[](int index) {return _grid[index];}
};

std::ostream& operator<<(std::ostream& stream, const Board& b) {
	for (size_t i = 0; i < WIDTH; i++) {
		if (!i) stream << "X ";
		stream << i+1 << " ";
	}
	stream << endl;
	// cout << "_ _ _ _ _ _ _ _ _\n"; 
	for (size_t i = 0; i < HEIGHT+1; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			if (!j) stream  << "| ";
			stream << b[i][j] << " ";
		}
		stream << "|" << endl;
	}
	stream << endl;
	return stream;
}

bool	input(int &x) {
	string s; getline(cin, s);
	try {
		x = stoi(s);}
	catch(std::exception& e) {
		x = 0;
	}
	if ((x >= 1 && x <= 7))
		return true;
	cerr << "Invalid inputs\n";
	return false;
}

int		main()
{
	int x = 0, turn = 1;
	bool ret;
	Board b;

	cout << b;
	while (1)
	{
		cout << "Player" << (turn == 1 ? turn : 2) << ": ";
		if ((ret = input(x)))
			b.Reflect_Input(x, turn);
		cout << b;
		if (b.ValidateBoard(x, turn))
		{
			cout << "Winner: Player" << (turn == 1 ? turn : 2) << endl;
			return 0;
		}
		if (ret)
			turn *= -1;
	}
	return 0;
}
