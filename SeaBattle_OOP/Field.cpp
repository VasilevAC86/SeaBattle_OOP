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

bool Field::Exam_Position(int row, int col, int num) {
	if (matrix_[row][col].State() != '0')	// если клетка занята
		return false;
	int size = fleet_.at(num).Size(); // Переменная для локального хранения размера корабля
	if (size == 1) {
		// Цикл проверки смежных клеток ниже и выше переданной переданной точки
		for (int i = col - 1; i <= col + 1; ++i) {
			if (i < 0 || i >= _SIZE) // если вышли за пределы поля
				continue;
			if (row - 1 >= 0) // если вышли за пределы поля
				if (matrix_[row-1][i].State() == '1')
					return false;
			if ((row + 1) < _SIZE) // если вышли за пределы поля
				if (matrix_[row+1][i].State() == '1')
					return false;
		}
		// Проверка смежных клеток справа и слева переданной переданной точки
		if (col - 1 >= 0) // если не вышли за пределы поля
			if (matrix_[row][col-1].State() == '1')
				return false;
		if (col + 1 < _SIZE) // если не вышли за пределы поля
			if (matrix_[row][col+1].State() == '1')
				return false;
		// Если одноклеточный корабль можно расположить, то располагаем его в клетке (row, col)
		matrix_[row][col].State('1'); // Занимаем клетку поля		
		matrix_[row][col].Set_Num_Ship(num); // Говорим клетке, какому кораблю она принадлежит
		fleet_[num].Point(&matrix_[row][col]); // Записываем адрес точки вставки корабля		
	}
	else { // Проверка и расположение многоклеточного корабля
		char vector = Orientation(row, col, size);
		if (vector == 'x') // если многоклеточный корабль расположить по правилам игры не получилось
			return false;
		else { // если получилось, то заполняем данные корабля и клеток поля
			fleet_.at(num).Point(&matrix_[row][col]); // Записываем адрес точки вставки корабля			
			fleet_.at(num).Vector(vector); // Указываем направление размещения корабля относительно точки вставки				
			if (vector == '>')
				for (int i = 0; i < size; ++i) {
					matrix_[row][col + i].State('1');
					matrix_[row][col + i].Set_Num_Ship(num);					
				}
			else
				if (vector == 'v')
					for (int i = 0; i < size; ++i) {
						matrix_[row + i][col].State('1');
						matrix_[row + i][col].Set_Num_Ship(num);						
					}
				else
					if (vector == '<')
						for (int i = 0; i < size; ++i) {
							matrix_[row][col - i].State('1');
							matrix_[row][col - 1].Set_Num_Ship(num);							
						}
					else
						if (vector == '^')
							for (int i = 0; i < size; ++i) {
								matrix_[row - i][col].State('1');
								matrix_[row - i][col].Set_Num_Ship(num);								
							}
		}
	}
}

char Field::Orientation(int row, int col, int size) {
	bool key = true; // Переменная для хранения кода ошибки расположения корабля (true - можно расположить, false - нельзя)				
	if (col + size <= _SIZE) { // если не вышли за пределы поля справа, то проверям, можно ли расположить корабль слева направо
		// Цикл проверки смежных клеток ниже и выше располагаемого направо относительно (row, col) корабля
		for (int i = col - 1; i <= col + size; ++i) {
			if (i < 0)
				continue;
			if (row - 1 >= 0) // если не вышли за пределы поля
				if (matrix_[row-1][i].State() == '1') {
					key = false;
					break; // нет смысла дальше крутить цикл
				}
			if (row + 1 < _SIZE) // если не вышли за пределы поля
				if (matrix_[row+1][i].State() == '1') {
					key = false;
					break;
				}
			if (matrix_[row][i].State() == '1') {
				key = false;
				break;
			}
		}
		if (key)
			return '>'; // Если корабль можно расположить справа налево, то возвращаем символ '>'
	}
	// Если корабль невозможно расположить слева направо, то начинаем крутить его по часовой стрелке
	key = true;
	if (row + size <= _SIZE) {
		for (int i = row - 1; i <= row + size; ++i) {
			if (i < 0)
				continue;
			if (col - 1 >= 0)
				if (matrix_[i][col-1].State() == '1') {
					key = false;
					break;
				}
			if (col + 1 < _SIZE)
				if (matrix_[i][col+1].State() == '1') {
					key = false;
					break;
				}
			if (matrix_[i][col].State() == '1') {
				key = false;
				break;
			}
		}
		if (key)
			return 'v'; // Если корабль можно расположить сверху вниз, то возвращаем символ 'v'
	}
	// Если корабль невозможно расположить сверху вниз, то крутим его дальше по часовой стрелке
	key = true;
	if (col - size + 1 >= 0) {
		for (int i = col + 1; i >= col - size; --i) {
			if (i > _SIZE)
				continue;
			if (row - 1 >= 0)
				if (matrix_[row-1][i].State() == '1') {
					key = false;
					break;
				}
			if (row + 1 < _SIZE)
				if (matrix_[row+1][i].State() == '1') {
					key = false;
					break;
				}
			if (matrix_[row][i].State() == '1') {
				key = false;
				break;
			}
		}
		if (key)
			return '<'; // Если корабль можно расположить справо налево, то возвращаем символ '<'
	}
	// Если корабль невозможно расположить справо налево, то крутим его дальше по часовой стрелке
	key = true;
	if (row - size + 1 >= 0) {
		for (int i = row + 1; i >= row - size; --i) {
			if (i < 0)
				continue;
			if (col - 1 >= 0)
				if (matrix_[i][col-1].State() == '1') {
					key = false;
					break;
				}
			if (col + 1 < _SIZE)
				if (matrix_[i][col+1].State() == '1') {
					key = false;
					break;
				}
			if (matrix_[i][col].State() == '1') {
				key = false;
				break;
			}
		}
		if (key)
			return '^'; // Если корабль можно расположить снизу вверх, то возвращаем символ '^'
	}
	return 'x'; // Если корабль невозможно расположить никак, то возвращаем символ 'x'
}

void Field::Rotation(int row, int col, int num) {
	int size = fleet_.at(num).Size(); // Переменная для локального хранения размера корабля
	if (fleet_.at(num).Vector() == '>')
		if (Exam_Turn_Down(row, col, size)) {
			for (int i = 1; i < size; ++i) {
				matrix_[row][col+i].State('0');
				matrix_[row+i][col].State('1');
				fleet_.at(num).Vector('v');
			}
			return;
		}
		else
			if (Exam_Turn_Left(row, col, size)) {
				for (int i = 1; i < size; ++i) {
					matrix_[row][col+i].State('0');
					matrix_[row][col-i].State('1');
					fleet_.at(num).Vector('<');
				}
				return;
			}
			else
				if (Exam_Turn_Up(row, col, size)) {
					for (int i = 1; i < size; ++i) {
						matrix_[row][col+i].State('0');
						matrix_[row-i][col].State('1');
						fleet_.at(num).Vector('^');
					}
					return;
				}
	if (fleet_.at(num).Vector() == 'v')
		if (Exam_Turn_Left(row, col, size)) {
			for (int i = 1; i < size; ++i) {
				matrix_[row+i][col].State('0');
				matrix_[row][col-i].State('1');
				fleet_.at(num).Vector('<');
			}
			return;
		}
		else
			if (Exam_Turn_Up(row, col, size)) {
				for (int i = 1; i < size; ++i) {
					matrix_[row+i][col].State('0');
					matrix_[row-i][col].State('1');
					fleet_.at(num).Vector('^');
				}
				return;
			}
			else
				if (Exam_Turn_Right(row, col, size)) {
					for (int i = 1; i < size; ++i) {
						matrix_[row+i][col].State('0');
						matrix_[row][col+i].State('1');
						fleet_.at(num).Vector('>');						
					}
					return;
				}

	if (fleet_.at(num).Vector() == '<')
		if (Exam_Turn_Up(row, col, size)) {
			for (int i = 1; i < size; ++i) {
				matrix_[row][col-i].State('0');
				matrix_[row-i][col].State('1');
				fleet_.at(num).Vector('^');
			}
			return;
		}
		else
			if (Exam_Turn_Right(row, col, size)) {
				for (int i = 1; i < size; ++i) {
					matrix_[row][col-i].State('0');
					matrix_[row][col+i].State('1');
					fleet_.at(num).Vector('>');
				}
				return;
			}
			else
				if (Exam_Turn_Down(row, col, size)) {
					for (int i = 1; i < size; ++i) {
						matrix_[row][col-i].State('0');
						matrix_[row+1][col].State('1');
						fleet_.at(num).Vector('v');
					}
					return;
				}
	if (fleet_.at(num).Vector() == '^') {
		if (Exam_Turn_Right(row, col, size)) {
			for (int i = 1; i < size; ++i) {
				matrix_[row-i][col].State('0');
				matrix_[row][col+i].State('1');
				fleet_.at(num).Vector('>');
			}
			return;
		}
		else
			if (Exam_Turn_Down(row, col, size)) {
				for (int i = 1; i < size; ++i) {
					matrix_[row-i][col].State('0');
					matrix_[row+i][col].State('1');
					fleet_.at(num).Vector('v');
				}
				return;
			}
			else
				if (Exam_Turn_Left(row, col, size)) {
					for (int i = 1; i < size; ++i) {
						matrix_[row-i][col].State('0');
						matrix_[row][col-i].State('1');
						fleet_.at(num).Vector('<');
					}
					return;
				}
	}
	std::cout << std::endl << "\033[91mTurning is impossible\033[0m" << std::endl;
	system("pause");
}

bool Field::Exam_Turn_Down(int row, int col, int size) {
	if (row + size <= _SIZE)
		for (int i = row + 2; i <= row + size; ++i) {
			if (col - 1 >= 0)
				if (matrix_[i][col-1].State() == '1')
					return false;
			if (col + 1 < _SIZE)
				if (matrix_[i][col+1].State() == '1')
					return false;
			if (matrix_[i][col].State() == '1')
				return false;
		}
	else
		return false;
	return true;
}

bool Field::Exam_Turn_Left(int row, int col, int size) {
	if (col - size + 1 >= 0)
		for (int i = col - 2; i >= col - size; --i) {
			if (row - 1 >= 0)
				if (matrix_[row-1][i].State() == '1')
					return false;
			if (row + 1 < _SIZE)
				if (matrix_[row+1][i].State() == '1')
					return false;
			if (matrix_[row][i].State() == '1')
				return false;
		}
	else
		return false;
	return true;
}

bool Field::Exam_Turn_Up(int row, int col, int size) {
	if (row - size + 1 >= 0)
		for (int i = row - 2; i >= row - size; --i) {
			if (col - 1 >= 0)
				if (matrix_[i][col-1].State() == '1')
					return false;
			if (col + 1 < _SIZE)
				if (matrix_[i][col+1].State() == '1')
					return false;
			if (matrix_[i][col].State() == '1')
				return false;
		}
	else
		return false;
	return true;
}

bool Field::Exam_Turn_Right(int row, int col, int size) {
	if (col + size <= _SIZE)
		for (int i = col + 2; i <= col + size; ++i) {
			if (row - 1 >= 0)
				if (matrix_[row-1][i].State() == '1')
					return false;
			if (row + 1 < _SIZE)
				if (matrix_[row+1][i].State() == '1')
					return false;
			if (matrix_[row][i].State() == '1')
				return false;
		}
	else
		return false;
	return true;
}


