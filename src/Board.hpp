#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>
#include <string>

using namespace std;

#define WIDTH 7
#define HEIGHT 6
#define Empty '.'

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
	bool	ValidateBoard(int x, int turn) {
		string search = turn < 0 ? "xxxx" : "oooo";
		if (_grid[Y].find(search) != string::npos) {
			return true;
		}
		string row;
		for (size_t i = 0; i < WIDTH; i++)
			row.push_back(_grid[i][x-1]);
		if (row.find(search) != string::npos) {
			return true;
		}
		/* 斜め↘︎ */
		string diag;
		int i = Y, j = x-1;
		for (j = x-1; j > 0 && i > 0; j--, i--)
			;
		// cout << "I:" << i <<  ",J:" << j << endl;
		for (; i < HEIGHT && j < WIDTH; i++, j++) {
			diag.push_back(_grid[i][j]);
		}
		if (diag.find(search) != string::npos) {
			return true;
		}

		/* 斜め↙︎ */
		i = Y, j = x-1;
		diag.clear();
		for (; j < WIDTH && i > 0; j++, i--)
			;
		for (; i < HEIGHT && j > 0; i++, j--) {
			diag.push_back(_grid[i][j]);
		}
		if (i < HEIGHT)
			diag.push_back(_grid[i][j]);
		if (diag.find(search) != string::npos) {
			return true;
		}
		// cout << diag;
		cout << endl;
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

#endif