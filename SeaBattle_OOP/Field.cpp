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
