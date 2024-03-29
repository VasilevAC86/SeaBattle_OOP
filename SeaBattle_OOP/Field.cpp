#include "Field.hpp"
#include<iostream>
#include"Global.hpp"

Field::Field() {
	for (int i = 0; i < _SIZE; ++i)
		for (int j = 0; j < _SIZE; ++j) {			
			matrix_[i][j].Hor(i + 1);
			matrix_[i][j].Vert('A' + j);
			matrix_[i][j].State('0');			
		}
}

void Field::Fill_in() {
	
}


