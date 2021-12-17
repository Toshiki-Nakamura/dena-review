#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>
#include <string>

using namespace std;

#define WIDTH 7
#define HEIGHT 6
#define Empty '.'
#define GREEN "\033[32m"
#define BLUE "\033[36m"
#define RED "\033[31m"
#define RESET "\033[0m"

class Board {
private:
	vector<string> _grid;
	int			Y;
public: 
	Board() : _grid(7, string(7, Empty)) {_grid[6] = string(7, '_');}
	~Board() {}
	bool	Reflect_Input(int x, int turn) {
		x--;
		if (_grid[0][x] != Empty)
			return false;
		for (size_t i = 0; i < HEIGHT; i++) {
			if (_grid[i+1][x] != Empty) {
				if (turn < 0) _grid[i][x] = 'x';
				else  _grid[i][x] = 'o';
				Y = i;
				return true;
			}
		}
		return false;
	}
	string	get_row(int y) {
		return _grid[y];
	}
	string	get_col(int x) {
		string col;
		for (size_t i = 0; i < WIDTH; i++)
			col.push_back(_grid[i][x-1]);
		return col;
	}
	string	get_right_diag(int x) {
		string diag;
		int i = Y, j = x-1;
		for (j = x-1; j > 0 && i > 0; j--, i--)
			;
		for (; i < HEIGHT && j < WIDTH; i++, j++) {
			diag.push_back(_grid[i][j]);
		}
		return diag;
	}
	string	get_left_diag(int x) {
		int	i = Y, j = x-1;
		string diag;
		for (; j < WIDTH && i > 0; j++, i--)
			;
		for (; i < HEIGHT && j > 0; i++, j--) {
			diag.push_back(_grid[i][j]);
		}
		if (i < HEIGHT)
			diag.push_back(_grid[i][j]);
		return diag;
	}
	bool	ValidateBoard(int x, int turn) {
		string search = turn < 0 ? "xxxx" : "oooo";

		string row = get_row(Y);
		if (row.find(search) != string::npos) {
			return true;
		}
		string col = get_col(x);
		if (col.find(search) != string::npos) {
			return true;
		}
		string diag = get_right_diag(x);
		if (diag.find(search) != string::npos) {
			return true;
		}
		diag.clear();
		diag = get_left_diag(x);
		if (diag.find(search) != string::npos) {
			return true;
		}
		cout << endl;
		return false;
	}
	std::string const &operator[](int index) const {return _grid[index];}
	std::string &operator[](int index) {return _grid[index];}
};

std::ostream& operator<<(std::ostream& stream, const Board& b) {
	for (size_t i = 0; i < WIDTH; i++) {
		if (!i) stream << "  ";
		stream << i+1 << " ";
	}
	stream << endl;
	for (size_t i = 0; i < HEIGHT+1; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			if (!j) stream  << "| ";
			if (b[i][j] == 'o')
				stream << GREEN << b[i][j] << " " << RESET;
			else if (b[i][j] == 'x')
				stream << BLUE << b[i][j] << " " << RESET;
			else
				stream << b[i][j] << " ";
		}
		stream << "|" << endl;
	}
	stream << endl;
	return stream;
}

#endif
