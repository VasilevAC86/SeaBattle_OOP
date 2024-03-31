#include "Field.hpp"

Field::Field() {
	for (int i = 0; i < _SIZE; ++i)
		for (int j = 0; j < _SIZE; ++j) {
			matrix_[i][j].Hor(i);
			matrix_[i][j].Vert(j + 65);
		}
}
