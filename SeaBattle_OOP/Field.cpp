#include "Field.hpp"
#include<iostream>

Field::Field() {
	for (int i = 0; i < size_; ++i)
		for (int j = 0; j < size_; ++j) {			
			matrix_[i][j].Hor('A' + i);
			matrix_[i][j].Vert(j + 1);
			matrix_[i][j].State('0');
		}
}

void Field::Fill_in() {
	
}


