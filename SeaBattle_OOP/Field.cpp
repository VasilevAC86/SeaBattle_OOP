#include "Field.hpp"
#include<iostream>

Field::Field() {
	for (int i = 0; i < size_; ++i)
		for (int j = 0; j < size_; ++j) {			
			matrix_[i][j].Hor(i + 1);
			matrix_[i][j].Vert('A' + j);
			matrix_[i][j].State('0');			
		}
}

void Field::Fill_in() {
	
}


