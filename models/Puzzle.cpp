#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstddef>
#include <math.h>
#include "Puzzle.hpp"

int Puzzle::h(const Puzzle& current, const Puzzle& target) {
	// Heuristic that counts the fields out of position
	if (current.size != target.size)
		return 0;
	int out_pos = 0;
	for (int i = 0; i < current.size; i++)
		for (int j = 0; j < current.size; j++)
			if (current.board[i][j] != target.board[i][j])
				out_pos++;
	return out_pos;
}

int Puzzle::g(const Puzzle& current, const Puzzle& target) {
	// Heuristic that tells us how many positions away is the current field
	if (current.size != target.size)
		return 0;
	int cost = 0;
	int size = current.size;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			bool found = false;
			for (int f = 0; f < size && !found; f++) {
				for (int c = 0; c < size && !found; c++) {
					if (current.board[i][j] == target.board[f][c]) {
						cost += abs(f - i) + abs(c - j);
						found = true;
					}
				}
			}
			found = false;
		}
	}
	return cost;
}

Puzzle::Puzzle() {
	size = 3;
	x = y = 0;
	init_board();
}

Puzzle::Puzzle(const size_t& size, char** board) {
	this->size = size;
	this->board = board;
	this->x = this->y = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == '0') {
				this->x = i;
				this->y = j;
				return;
			}
		}
	}
}

Puzzle::Puzzle(const Puzzle& other) {
	x = other.x;
	y = other.y;
	size = other.size;
	init_board();
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = other.board[i][j];
}

Puzzle::~Puzzle() {
	for (int i = 0; i < size; i++)
		delete[] board[i];
	delete[] board;
	board = nullptr;
	x = y = size = 0;
}

void Puzzle::init_board() {
	board = new char* [size];
	for (int i = 0; i < size; i++) {
		board[i] = new char[size];
		for (int j = 0; j < size; j++)
			board[i][j] = 0;
	}
}

bool Puzzle::is_mov_valid(const size_t& i, const size_t& j) const {
	return (i >= 0 && i < size) && (j >= 0 && j < size);
}

bool Puzzle::move_left() {
	if (!is_mov_valid(x, y - 1))
		return false;
	std::swap(board[x][y - 1], board[x][y]);
	y--;
	return true;
}

bool Puzzle::move_right() {
	if (!is_mov_valid(x, y + 1))
		return false;
	std::swap(board[x][y + 1], board[x][y]);
	y++;
	return true;
}

bool Puzzle::move_up() {
	if (!is_mov_valid(x - 1, y))
		return false;
	std::swap(board[x - 1][y], board[x][y]);
	x--;
	return true;
}

bool Puzzle::move_down() {
	if (!is_mov_valid(x + 1, y))
		return false;
	std::swap(board[x + 1][y], board[x][y]);
	x++;
	return true;
}

std::string Puzzle::to_string() const {
	std::stringstream ss;
	for (int i = 0; i < size; i++) {
		ss << "|";
		for (int j = 0; j < size; j++)
			ss << std::setw(2) << (board[i][j] != '0' ? board[i][j] : ' ') << std::setw(2) << "|";
		ss << std::endl;
	}
	return ss.str();
}

Puzzle& Puzzle::operator=(const Puzzle& other) {
	if (this == &other)
		return *this;
	delete this;
	return *(new Puzzle(other));
}

bool Puzzle::operator==(const Puzzle& other) const {
	if (size != other.size)
		return false;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] != other.board[i][j])
				return false;
	return true;
}

bool Puzzle::operator!=(const Puzzle& other) const {
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle) {
	return out << puzzle.to_string();
}