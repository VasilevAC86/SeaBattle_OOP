#include "Field.hpp"

Field::Field() {
	for (int i = 0; i < _SIZE; ++i)
		for (int j = 0; j < _SIZE; ++j) {
			matrix_[i][j].Hor(i);
			matrix_[i][j].Vert(j + 65);
		}
}

void Field::Clear() {	
	int row, col; // Кординаты точки вставки корабля
	for (int i = 0; i < fleet_.size(); ++i) {
		row = fleet_.at(i).Point()->Hor();
		col = fleet_.at(i).Point()->Vert() - 65;
		if (fleet_.at(i).Size() == 1) {
			fleet_.at(i).Point(nullptr);
			fleet_.at(i).Size(0);
			matrix_[row][col].State('0');
		}
		else {				
			if (fleet_.at(i).Vector() == '>') 
				for (int j = 0; j < fleet_.at(i).Size(); ++j)
					matrix_[row][col + j].State('0');
			if (fleet_.at(i).Vector() == 'v')
				for (int j = 0; j < fleet_.at(i).Size(); ++j)
					matrix_[row + j][col].State('0');
			if (fleet_.at(i).Vector() == '<')
				for (int j = 0; j < fleet_.at(i).Size(); ++j)
					matrix_[row][col - j].State('0');
			if (fleet_.at(i).Vector() == '^')
				for (int j = 0; j < fleet_.at(i).Size(); ++j)
					matrix_[row - j][col].State('0');
			fleet_.at(i).Point(nullptr);
			fleet_.at(i).Size(0);
			fleet_.at(i).Vector('0');
		}
	}
}

void Field::Snake(int num) {
	int row = fleet_.at(num).Point()->Hor(); // Координата ряда поля точки вставки корабля
	int col = fleet_.at(num).Point()->Vert() - 65; // Координата столбца поля точки вставки корабля
	int size = fleet_.at(num).Size(); // Размер корабля
	if (fleet_.at(num).Vector() == '0') { // Если корабль оноклеточный
		if (row + 1 < _SIZE) 
			for (int i = col - 1; i <= col + 1; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[row + 1][i].State('3');
			}
		if (row - 1 >= 0)
			for (int i = col - 1; i <= col + 1; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[row - 1][i].State('3');
			}
		if (col - 1 >= 0)
			matrix_[row][col - 1].State('3');
		if (col + 1 < _SIZE)
			matrix_[row][col + 1].State('3');
		return;
	}
	// Если корабль многоклеточный
	if (fleet_.at(num).Vector() == '>') {
		if (row + 1 < _SIZE) 
			for (int i = col - 1; i <= col + size; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[row + 1][i].State('3');
			}
		if (row - 1 >= 0)
			for (int i = col - 1; i <= col + size; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[row - 1][i].State('3');
			}
		if (col - 1 >= 0)
			matrix_[row][col - 1].State('3');
		if (col + size < _SIZE)
			matrix_[row][col + size].State('3');
		return;
	}
	if (fleet_.at(num).Vector() == 'v') {
		if (col - 1 >= 0)
			for (int i = row - 1; i <= row + size; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[i][col - 1].State('3');
			}
		if (col + 1 < _SIZE)
			for (int i = row - 1; i <= row + size; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[i][col + 1].State('3');
			}
		if (row - 1 >= 0)
			matrix_[row - 1][col].State('3');
		if (row + size < _SIZE)
			matrix_[row + size][col].State('3');
		return;
	}
	if (fleet_.at(num).Vector() == '<') {
		if (row + 1 < _SIZE) 
			for (int i = col + 1; i >= col - size; --i) {
				if (i < 0 || i > _SIZE)
					continue;
				matrix_[row + 1][i].State('3');
			}		
		if (row - 1 >= 0)
			for (int i = col + 1; i >= col - size; --i) {
				if (i < 0 || i > _SIZE)
					continue;
				matrix_[row - 1][i].State('3');
			}
		if (col + 1 < _SIZE)
			matrix_[row][col + 1].State('3');
		if (col - size >= 0)
			matrix_[row][col - size].State('3');
		return;
	}
	if (fleet_.at(num).Vector() == '^') {
		if (col - 1 >= 0)
			for (int i = row - 1; i >= row + size; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[i][col - 1].State('3');
			}
		if (col + 1 < _SIZE)
			for (int i = row - 1; i >= row + size; ++i) {
				if (i < 0 || i == _SIZE)
					continue;
				matrix_[i][col + 1].State('3');
			}
		if (row + 1 < _SIZE)
			matrix_[row + 1][col].State('3');
		if (row - size < _SIZE)
			matrix_[row - size][col].State('3');
	}
}
