#include "Game.hpp"
#include"Global.hpp"
#include"Cell.hpp"
#include"Field.hpp"

#include<Windows.h>
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

///Глобальные константы и переменнные
// Первая строчка таблицы доступных кораблей
const std::string _HEADER = " Position |       1        |        2        |       3       |       4       ";
// Длина первой строчки таблицы доступных кораблей
int _TABLE_LENGTH = _HEADER.length(); // Длина таблицы доступных кораблей в символах
// Код символа корабля в занятой клетки из ASCII-таблицы
const char _SHIP = 219;

/*
* \brief Внешняя функция проверки возможности установки корябля размером size по координате (row, col)
* \details Функция возвращает направление размещения корабля по правилам относительно точки вставки (row, col).
* Если корабль по правилам разместить не удаётся, то функция возвращает "x".
*/
char Orientation(Field* p, int row, int col, int size) {	
	bool key = true; // Переменная для хранения кода ошибки расположения корабля (true - можно расположить, false - нельзя)				
	if (col + size <= _SIZE) { // если не вышли за пределы поля справа, то проверям, можно ли расположить корабль слева направо
		// Цикл проверки смежных клеток ниже и выше располагаемого направо относительно (row, col) корабля
		for (int i = col - 1; i <= col + size; ++i) {
			if (i < 0)
				continue;
			if (row - 1 >= 0) // если не вышли за пределы поля
				if ((*p).At_Get(row - 1, i).State() == '1') {
					key = false;
					break; // нет смысла дальше крутить цикл
				}							
			if (row + 1 < _SIZE) // если не вышли за пределы поля
				if ((*p).At_Get(row + 1, i).State() == '1') {
					key = false;
					break;
				}
			if ((*p).At_Get(row, i).State() == '1') {
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
				if ((*p).At_Get(i, col - 1).State() == '1') {
					key = false;
					break;
				}
			if (col + 1 < _SIZE)
				if ((*p).At_Get(i, col + 1).State() == '1') {
					key = false;
					break;
				}
			if ((*p).At_Get(i, col).State() == '1') {
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
				if ((*p).At_Get(row - 1, i).State() == '1') {
					key = false;
					break;
				}
			if (row + 1 < _SIZE)
				if ((*p).At_Get(row + 1, i).State() == '1') {
					key = false;
					break;
				}
			if ((*p).At_Get(row, i).State() == '1') {
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
				if ((*p).At_Get(i, col - 1).State() == '1') {
					key = false;
					break;
				}
			if (col + 1 < _SIZE)
				if ((*p).At_Get(i, col + 1).State() == '1') {
					key = false;
					break;
				}
			if ((*p).At_Get(i, col).State() == '1') {
				key = false;
				break;
			}
		}		
		if (key)
			return '^'; // Если корабль можно расположить снизу вверх, то возвращаем символ '^'
	}
	return 'x'; // Если корабль невозможно расположить никак, то возвращаем символ 'x'
}

/*
* \brief Внешняя функция проверки точки вставки нового корабля
* \details Если точка вставки соприкасается с уже существующим кораблём, или 
* игрок пытается установить корабль в уже занятую клетку, функция возвращает false
*/
bool Exam_Position(Field* p, int row, int col, int num) {	
	if ((*p).At_Get(row, col).State() != '0')	// если клетка занята
		return false;	
	int size = (*p).At_Get_Ship(num).Size(); // Переменная для локального хранения размера корабля
	if (size == 1) {
		// Цикл проверки смежных клеток ниже и выше переданной переданной точки
		for (int i = col - 1; i <= col + 1; ++i) {
			if (i < 0 || i >= _SIZE) // если вышли за пределы поля
				continue;
			if (row - 1 >= 0) // если вышли за пределы поля
				if ((*p).At_Get(row - 1, i).State() == '1')
					return false;
			if ((row + 1) < _SIZE) // если вышли за пределы поля
				if ((*p).At_Get(row + 1, i).State() == '1')
					return false;
		}
		// Проверка смежных клеток справа и слева переданной переданной точки
		if (col - 1 >= 0) // если не вышли за пределы поля
			if ((*p).At_Get(row, col - 1).State() == '1')
				return false;
		if (col + 1 < _SIZE) // если не вышли за пределы поля
			if ((*p).At_Get(row, col + 1).State() == '1')
				return false;
		// Если одноклеточный корабль можно расположить, то располагаем его в клетке (row, col)
		(*p).At_Set(row, col)->State('1'); // Занимаем клетку поля
		(*p).At_Set(row, col)->Hor(row); // Записываем поле "горизонталь" объекта "Клетка"
		(*p).At_Set(row, col)->Vert(col + 65); // Записываем поле "вертикаль" объекта "Клетка"
		(*p).At_Set_Ship(num).Point((*p).At_Set(row,col)); // Записываем адрес точки вставки корабля
	}
	else { // Проверка и расположение многоклеточного корабля
		char vector = Orientation(p, row, col, size);
		if (vector == 'x') // если многоклеточный корабль расположить по правилам игры не получилось
			return false;
		else { // если получилось, то заполняем данные корабля и клеток поля
			(*p).At_Set_Ship(num).Point((*p).At_Set(row, col)); // Записываем адрес точки вставки корабля
			(*p).At_Set_Ship(num).Vector(vector); // Указываем направление размещения корабля относительно точки вставки	
			if (vector == '>') 
				for (int i = 0; i < size; ++i) 
					(*p).At_Set(row, col + i)->State('1');									
			else
				if (vector == 'v')
					for (int i = 0; i < size; ++i) 
						(*p).At_Set(row + i, col)->State('1');					
				else
					if (vector == '<')
						for (int i = 0; i < size; ++i) 
							(*p).At_Set(row, col - i)->State('1');							
					else
						if (vector == '^')
							for (int i = 0; i < size; ++i) 
								(*p).At_Set(row - i, col)->State('1');								
		}
	}

	return true;
}

///Внешняя функция проверки возможности поворота корабля вниз относительно точки (row, col)
bool Exam_Turn_Down(Field* p, int row, int col, int size) {
	if (row + size <= _SIZE)
		for (int i = row + 2; i <= row + size; ++i) {
			if (col - 1 >= 0)
				if ((*p).At_Get(i, col - 1).State() == '1')
					return false;
			if (col + 1 < _SIZE)
				if ((*p).At_Get(i, col + 1).State() == '1')
					return false;
			if ((*p).At_Get(i, col).State() == '1')
				return false;
		}
	else
		return false;
	return true;
}

///Внешняя функция проверки возможности поворота корабля влево относительно точки (row, col)
bool Exam_Turn_Left(Field* p, int row, int col, int size) {
	if (col - size + 1 >= 0)
		for (int i = col - 2; i >= col - size; --i) {
			if (row - 1 >= 0)
				if ((*p).At_Get(row - 1, i).State() == '1')
					return false;
			if (row + 1 < _SIZE)
				if ((*p).At_Get(row + 1, i).State() == '1')
					return false;
			if ((*p).At_Get(row, i).State() == '1')
				return false;
		}
	else
		return false;
	return true;
}

///Внешняя функция проверки возможности поворота корабля вверх относительно точки (row, col)
bool Exam_Turn_Up(Field* p, int row, int col, int size) {
	if (row - size + 1 >= 0)
		for (int i = row - 2; i >= row - size; --i) {
			if (col - 1 >= 0)
				if ((*p).At_Get(i, col - 1).State() == '1')
					return false;
			if (col + 1 < _SIZE)
				if ((*p).At_Get(i, col + 1).State() == '1')
					return false;
			if ((*p).At_Get(i, col).State() == '1')
				return false;
		}
	else
		return false;
	return true;
}

///Внешняя функция проверки возможности поворота корабля вниз относительно точки (row, col)
bool Exam_Turn_Right(Field* p, int row, int col, int size) {
	if (col + size <= _SIZE)
		for (int i = col + 2; i <= col + size; ++i) {
			if (row - 1 >= 0)
				if ((*p).At_Get(row - 1, i).State() == '1')
					return false;
			if (row + 1 < _SIZE)
				if ((*p).At_Get(row + 1, i).State() == '1')
					return false;
			if ((*p).At_Get(row, i).State() == '1')
				return false;
		}
	else
		return false;
	return true;
}

/*
* \brief Внешняя функция поворота корабля на игровом поле
* \details Функция поворачивает установленный на поле корабль один раз по часовой стрелке. 
* Если корабль повернуть не удаётся, функция сообщает об этом.
*/
void Rotation(Field* p, int row, int col, int num) {
	int size = (*p).At_Get_Ship(num).Size(); // Переменная для локального хранения размера корабля
	if ((*p).At_Get_Ship(num).Vector() == '>') 
		if (Exam_Turn_Down(p, row, col, size)) {
			for (int i = 1; i < size; ++i) {
				(*p).At_Set(row, col + i)->State('0');
				(*p).At_Set(row + i, col)->State('1');
				(*p).At_Set_Ship(num).Vector('v');
			}
			return;
		}
		else
			if (Exam_Turn_Left(p, row, col, size)) {
				for (int i = 1; i < size; ++i) {
					(*p).At_Set(row, col + i)->State('0');
					(*p).At_Set(row, col - i)->State('1');
					(*p).At_Set_Ship(num).Vector('<');
				}
				return;
			}
			else
				if (Exam_Turn_Up(p, row, col, size)) {
					for (int i = 1; i < size; ++i) {
						(*p).At_Set(row, col + i)->State('0');
						(*p).At_Set(row - i, col)->State('1');
						(*p).At_Set_Ship(num).Vector('^');
					}
					return;
				}				
	if ((*p).At_Get_Ship(num).Vector() == 'v')
		if (Exam_Turn_Left(p, row, col, size)) {
			for (int i = 1; i < size; ++i) {
				(*p).At_Set(row + i, col)->State('0');
				(*p).At_Set(row, col - i)->State('1');
				(*p).At_Set_Ship(num).Vector('<');
			}
			return;
		}
		else
			if (Exam_Turn_Up(p, row, col, size)) {
				for (int i = 1; i < size; ++i) {
					(*p).At_Set(row + i, col)->State('0');
					(*p).At_Set(row - i, col)->State('1');
					(*p).At_Set_Ship(num).Vector('^');
				}
				return;
			}
			else
				if (Exam_Turn_Right(p, row, col, size)) {
					for (int i = 1; i < size; ++i) {
						(*p).At_Set(row + i, col)->State('0');
						(*p).At_Set(row, col + i)->State('1');
						(*p).At_Set_Ship(num).Vector('>');
					}
					return;
				}
			
	if ((*p).At_Get_Ship(num).Vector() == '<')
		if (Exam_Turn_Up(p, row, col, size)) {
			for (int i = 1; i < size; ++i) {
				(*p).At_Set(row, col - i)->State('0');
				(*p).At_Set(row - i, col)->State('1');
				(*p).At_Set_Ship(num).Vector('^');
			}
			return;
		}
		else
			if (Exam_Turn_Right(p, row, col, size)) {
				for (int i = 1; i < size; ++i) {
					(*p).At_Set(row, col - i)->State('0');
					(*p).At_Set(row,col + i)->State('1');
					(*p).At_Set_Ship(num).Vector('>');
				}
				return;
			}
			else
				if (Exam_Turn_Down(p, row, col, size)) {
					for (int i = 1; i < size; ++i) {
						(*p).At_Set(row, col - i)->State('0');
						(*p).At_Set(row + i, col)->State('1');
						(*p).At_Set_Ship(num).Vector('v');
					}
					return;
				}
	if ((*p).At_Get_Ship(num).Vector() == '^') {
		if (Exam_Turn_Right(p, row, col, size)) {
			for (int i = 1; i < size; ++i) {
				(*p).At_Set(row - i, col)->State('0');
				(*p).At_Set(row, col + i)->State('1');
				(*p).At_Set_Ship(num).Vector('>');
			}
			return;
		}
		else
			if (Exam_Turn_Down(p, row, col, size)) {
				for (int i = 1; i < size; ++i) {
					(*p).At_Set(row - i, col)->State('0');
					(*p).At_Set(row + i, col)->State('1');
					(*p).At_Set_Ship(num).Vector('v');
				}
				return;
			}
			else
				if (Exam_Turn_Left(p, row, col, size)) {
					for (int i = 1; i < size; ++i) {
						(*p).At_Set(row - i, col)->State('0');
						(*p).At_Set(row, col - i)->State('1');
						(*p).At_Set_Ship(num).Vector('<');
					}
					return;
				}
	}
	std::cout << std::endl << "\033[91mTurning is impossible\033[0m" << std::endl;
	system("pause");
}

/*
* \brief Внешняя функция проверки наличия выбранного игроком типа корабля
* \details Если игрок вводит некорректные значения (<1 или > 4), функция просит игрока ввести размер корабля заново.
* Функция возвращает размер выбранног игроком корабля после проверки введённого игроком значения
*/
int Check_Position_Ship (std::string &position_text) {
	// Если введённое пользователем значение не в диапазоне от 1 до 4
	while (position_text.length() > 1 || position_text[0] < 49 || position_text[0] > 52) {
		std::cout << "\033[91mInput error!\033[0m" << std::endl << "Enter the \033[96mposition\033[0m number of the ship one more time -> ";
		std::cin >> position_text;
	}
	return(stoi(position_text));
}

/// Внешняя функция определения координаты ряда игрового поля
int Enter_Row() {
	int row = 1; // Переменная для хранения координаты строки поля
	std::string row_text; // Переменная для хранения строки, введённой пользователем (вводим строку для исключения ошибки ввода с крахом программы)
	std::cout << "\033[93mEnter the coordinate of the row\033[0m (for example 5) -> ";
	std::cin >> row_text;
	bool key = true; // Переменная для хранения кода ошибки (true - значение, введённое пользователем от 1 до 10, иначе false)
	int length = row_text.length(); // Длина введённой пользователем строки	
	// Если пользователь ввёл два символа, первый не 1, второй не 0	
	if (length == 2 && row_text != "10")
		key = false;
	else
		if (length == 1 && (char(row_text[0]) < '1' || char(row_text[0] > '9'))) // Если пользователь ввёл 0 или любой символ не числа 
			key = false;
		else
			if (length > 2) // Если пользователь явно ввёл не число от 1 до 10
				key = false;
	while (key == false) {
		std::cout << "\033[91mInput error!\033[0m\n\033[93mEnter the coordinate of the row\033[0m (for example 5) in the range from 1 to 10 one more time -> ";
		std::cin >> row_text;
		length = row_text.length();
		if (length == 2 && row_text == "10")
			key = true;
		else
			if (length == 1 && (char(row_text[0]) > '0' && char(row_text[0]) <= '9'))
				key = true;
	}
	row = stoi(row_text);
	return --row; // -1 для приведения координаты к индексу массива
}

/// Внешняя функция определения координаты столбца игрового поля
int Enter_Col() {
	std::string col_text; // Переменная для хранения строки, введённой пользователем (вводим строку для исключения ошибки ввода с крахом программы)
	std::cout << "\033[93mEnter the coordinate of the column\033[0m (for example B or b) -> ";
	std::cin >> col_text;
	char column = toupper(col_text[0]);// Переменная для хранения координаты столбца поля в виде буквы
	while (col_text.length() > 1 || column < 65 || column > 74) { // Пока введённое пользователем значение не является буквой от A до J включительно
		std::cout << "\033[91mInput error!\033[0m\n\033[93mEnter the coordinate of the column\033[0m (for example B or b) in the range from A to J (or from a to j) one more time -> ";
		std::cin >> col_text;
		column = toupper(col_text[0]);
	}
	return int(column) - 65; // Переводим код символа координаты столбца в индекс массива
}

/// Внешняя функция перемещения курсора в точку консоли с координатами x, y
void gotoxy(int x, int y) {
	COORD p = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

/// Внешняя функция получения текущей координаты консоли Х
int Xcoord() {
	CONSOLE_SCREEN_BUFFER_INFO info_x;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
	return info_x.dwCursorPosition.X;
}

/// Внешняя функция получения текущей координаты консоли Y
int Ycoord() {
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	return info_y.dwCursorPosition.Y;
}

/// Внешняя функция отрисовки горизонтальной черты в таблице доступных кораблей
void Print_Horizon() {
	for (int i = 0; i < _TABLE_LENGTH; ++i)
		std::cout << '-';
	std::cout << std::endl;
}

void Game::Hand(bool player) {	
	// Переменная для хранения позиции выбранного типа корабля в формате строки, введённой с клавиатуры
	std::string position_text; 		
	Player* p = &p1_; // Указатель на игрока, который будет расставлять корабли вручную
	if (!player)
		p = &p2_;
	Print_Player_Active(*p);
	do { // Цикл заполнения игрового поля кораблями	вручную		
		std::cout << "\n\033[93mEnter the\033[0m \033[96mposition\033[0m \033[93mnumber of the ship\033[0m -> ";
		std::cin >> position_text;				
		int size_ship = Check_Position_Ship(position_text); // Переменная для хранения размера корабля
		bool key = true; // Переменная для хранения кода ошибки (true - корабль можно поставить на поле, false - нельзя)
		// Цикл проверки выбранного пользователем корабля на доступноть его для выбора (есть ли корабль ещё в наличии?)
		// Итогом цикла должен быть разрешённый игрой корабль (размером size_ship) для установки на игровом поле
		do {
			if (size_ship == 1)
				if ((*p).Get_Stat().Num_1() < _QAUNTITY_1) {
					(*p).Set_Stat().Change_1(); // Увеличиваем общее кол-во кораблей и кол-во одноклеточных кораблей					
					key = true;
				}
				else {
					key = false;
					std::cout << "\033[91mYou don't have any more ships of this type! Choose a different type of ship\033[0m -> ";
					std::cin >> position_text;
					size_ship = Check_Position_Ship(position_text);
				}
			if (size_ship == 2)
				if ((*p).Get_Stat().Num_2() < _QAUNTITY_2) {
					(*p).Set_Stat().Change_2(); // Увеличиваем общее кол-во кораблей и кол-во двухклеточных кораблей
					key = true;
				}
				else {
					key = false;
					std::cout << "\033[91mYou don't have any more ships of this type! Choose a different type of ship\033[0m -> ";
					std::cin >> position_text;
					size_ship = Check_Position_Ship(position_text);
				}
			if (size_ship == 3)
				if ((*p).Get_Stat().Num_3() < _QAUNTITY_3) {
					(*p).Set_Stat().Change_3(); // Увеличиваем общее кол-во кораблей и кол-во трёхклеточных кораблей
					key = true;
				}
				else {
					key = false;
					std::cout << "\033[91mYou don't have any more ships of this type! Choose a different type of ship\033[0m -> ";
					std::cin >> position_text;
					size_ship = Check_Position_Ship(position_text);
				}
			if (size_ship == 4)
				if ((*p).Get_Stat().Num_4() < _QAUNTITY_4) {
					(*p).Set_Stat().Change_4(); // Увеличиваем общее кол-во кораблей и кол-во четырёхклеточных кораблей
					key = true;
				}
				else {
					key = false;
					std::cout << "\033[91mYou don't have any more ships of this type! Choose a different type of ship\033[0m -> ";
					std::cin >> position_text;
					size_ship = Check_Position_Ship(position_text);
				}
		} while (!key);
		// После того, как игра разрешила игроку разместить на поле корабль размером size_ship,
		// игра ставит этот корабль на поле, запрашивая у игрока координату точки вставки
		std::cout << "\033[93mEnter the coordinate of the field to install the ship\033[0m" << std::endl;
		int col = Enter_Col();
		int row = Enter_Row();		
		int num = (*p).Get_Stat().Num_All() - 1; // Локальная переменная для хранения порядкового номера корабля
		// Заполняем данные (размер и адрес точки вставки) выбранного пользователем объекта "Корабль"		
		(*p).Set_Field().At_Set_Ship(num).Size(size_ship); // Устанавливаем размер корабля	
		while(!Exam_Position(&(*p).Set_Field(), row, col, num)) { // Цикл проверки возможности вставки корабля в (row, col)
			std::cout << std::endl << "\033[91mThe ship can not be positioned at the specified coordinate!" << \
				std::endl << "\033[91mEnter the coordinate one more time." << std::endl;
			col = Enter_Col();
			row = Enter_Row();			
		}
		if (size_ship > 1) 
			(*p).Set_Field().At_Set(row, col)->State('r');
		system("cls");
		Print_Player_Active(*p);
		if (size_ship > 1) {
			char my_choise = '1'; // Переменная для хранения выбора пользователя
			do {
				std::cout << "\n\033[93mDo you want to rotate the ship?\033[0m ( \033[92m" << _SHIP << "\033[0m - ship's rotation point)" \
					<< std::endl << "Press \033[93m1\033[0m to YES \033[4mor\033[0m press \033[93many other key\033[0m to NO" \
					<< std::endl << "Your choise -> ";
				std::cin >> my_choise;
				if (my_choise != '1')
					break;
				Rotation(&(*p).Set_Field(), row, col, num);
				system("cls");
				Print_Player_Active(*p);
			} while (my_choise == '1');			
			(*p).Set_Field().At_Set(row, col)->State('1');
		}
	} while ((*p).Get_Stat().Num_All() != _QAUNTITY);
}

void Game::Auto(bool player) {
	Player* p = &p1_; // Указатель на игрока, который будет расставлять корабли вручную
	int row, col; // Координаты клетки вставки корабля
	int number; // Порядковый номер корабля в массиве fleet_
	char my_choice = '1'; // Перменная для хранения выбора пользователя
	if (!player)
		p = &p2_;
	srand(time(NULL));	
	while(my_choice == '1') { // Цикл формирования игрового поля игрока
		
		// Надо прописать:
		// 1. Очистку поля от клетот со статусами
		// 2. Очистку статистика игрока
		// 3. Очистку массива кораблей игрока

		for (int j = 0; j < _QAUNTITY_4; ++j) { // Устанавливаем четырёхклеточные корабли
			(*p).Set_Stat().Change_4(); // Изменяем статистику игрока (увеличиваем кол-во установленных кораблей)			
			number = (*p).Get_Stat().Num_All() - 1;
			(*p).Set_Field().At_Set_Ship(number).Size(_SIZE_4); // Устанавливаем размер корабля
			do {
				// Рандомно определяем координаты точки вставки корабля
				row = rand() % 10;
				col = rand() % 10;
			} while (!Exam_Position(&(*p).Set_Field(),row,col,number)); // Пока корабль не будет установлен
		}
		for (int j = 0; j < _QAUNTITY_3; ++j) { // Устанавливаем четырёхклеточные корабли
			(*p).Set_Stat().Change_3(); // Изменяем статистику игрока (увеличиваем кол-во установленных кораблей)			
			number = (*p).Get_Stat().Num_All() - 1;
			(*p).Set_Field().At_Set_Ship(number).Size(_SIZE_3); // Устанавливаем размер корабля
			do {
				// Рандомно определяем координаты точки вставки корабля
				row = rand() % 10;
				col = rand() % 10;
			} while (!Exam_Position(&(*p).Set_Field(), row, col, number)); // Пока корабль не будет установлен
		}
		for (int j = 0; j < _QAUNTITY_2; ++j) { // Устанавливаем четырёхклеточные корабли
			(*p).Set_Stat().Change_2(); // Изменяем статистику игрока (увеличиваем кол-во установленных кораблей)			
			number = (*p).Get_Stat().Num_All() - 1;
			(*p).Set_Field().At_Set_Ship(number).Size(_SIZE_2); // Устанавливаем размер корабля
			do {
				// Рандомно определяем координаты точки вставки корабля
				row = rand() % 10;
				col = rand() % 10;
			} while (!Exam_Position(&(*p).Set_Field(), row, col, number)); // Пока корабль не будет установлен
		}
		for (int j = 0; j < _QAUNTITY_1; ++j) { // Устанавливаем четырёхклеточные корабли
			(*p).Set_Stat().Change_1(); // Изменяем статистику игрока (увеличиваем кол-во установленных кораблей)			
			number = (*p).Get_Stat().Num_All() - 1;
			(*p).Set_Field().At_Set_Ship(number).Size(_SIZE_1); // Устанавливаем размер корабля
			do {
				// Рандомно определяем координаты точки вставки корабля
				row = rand() % 10;
				col = rand() % 10;
			} while (!Exam_Position(&(*p).Set_Field(), row, col, number)); // Пока корабль не будет установлен
		}
		Print_Player_Active((*p));
		std::cout << "Do you want to change your field?" << std::endl << "Press '1' if you want of press any other key if everything suit your"\
			<< std::endl << "Your choice -> ";
		std::cin >> my_choice;
	}		
}

void Viewer::Print_Player_Active(Player& p) {
	int counter_Cols = 64;// Счётчик букв-координат поля по кодам ASCII-таблицы
	char symbol;// Переменная для хранения буквенной координаты поля
	std::cout << "\033[92m" << p.Name() << "\033[0m" << std::endl << "\033[93mYour playing field:\033[0m" << std::endl;
	for (int i = 0; i <= _SIZE; ++i) { // 11-ый ряд - это ряд с обозначениями столбцов
		for (int j = 0; j < (_SIZE * 2 + 3); ++j) { // 23 столбца: 2 под наименования рядов, 10 под ячейки поля, 11 под границы яыеек поля
			if (i == 0) {
				if (j == 0 || j == 1)
					std::cout << ' ';
				else if (j % 2) {
					++counter_Cols;
					symbol = counter_Cols;
					std::cout << "\033[4m" << symbol << "\033[0m";
				}
				else if (j == 2)
					std::cout << ' ';
				else
					std::cout << "\033[93m|\033[0m";
			}
			if (j % 2 == 0 && j != 0 && i != 0)
				if (j == 2)
					std::cout << '|';
				else
					std::cout << "\033[93m|\033[0m";
			else if (i != 0 && j != 0 && j != 1)
				if (p.Get_Field().At_Get(i - 1, (j - 3) / 2).State() == '0') // Если клетка пустая
					std::cout << "\033[93m_\033[0m";
				else
					if (p.Get_Field().At_Get(i - 1, (j - 3) / 2).State() == '1') // Если клетка занята "живым" кораблём
						std::cout << _SHIP;
					else
						if (p.Get_Field().At_Get(i - 1, (j - 3) / 2).State() == '2') // Если корабль подбит
							std::cout << "\033[91m\033[4m" << 'X' << "\033[0m";
						else
							if (p.Get_Field().At_Get(i - 1, (j - 3) / 2).State() == 'r')
								std::cout << "\033[92m" << _SHIP << "\033[0m"; // Если корабль надо повернуть
							else
								std::cout << "\033[94m\033[4m" << '*' << "\033[0m"; // Если промах
			if (i > 0 && i < _SIZE)
				if (j == 0)
					std::cout << ' ';
				else
					if (j == 1)
						std::cout << "\033[4m" << i << "\033[0m";
			if (i == _SIZE) {
				if (j == 0)
					std::cout << "\033[4m" << 1 << "\033[0m";
				if (j == 1)
					std::cout << "\033[4m" << 0 << "\033[0m";
			}
		}
		std::cout << std::endl;
	}
	int x, y; // Текущие координаты курсора в консоли
	x = Xcoord();
	y = Ycoord();
	gotoxy(30, 2);
	std::cout << "\033[93mYour available fleet:\033[0m" << std::endl << std::endl;
	gotoxy(30, 3);
	// Вывод в консоль первой строчки таблицы кораблей
	std::cout << " Position |       \033[96m1\033[0m        |        \033[96m2\033[0m        |       \033[96m3\033[0m       |       \033[96m4\033[0m       \n";
	gotoxy(30, 4);
	Print_Horizon();	
	gotoxy(30, 5);
	// Вывод в консоль второй строчки таблицы кораблей
	std::cout << "  Title   | Four-deck ship | Three-deck ship | Two-deck ship | One-deck ship \n";
	gotoxy(30, 6);
	Print_Horizon();	
	gotoxy(30, 7);
	// Вывод в консоль третьей строчки таблицы		
	std::cout << "  Image   |       " << _SHIP << "        |       " << _SHIP << ' ' << _SHIP << "       |     " << _SHIP << ' ' << _SHIP << ' ' << _SHIP << "     |    " << _SHIP << ' ' << _SHIP << ' ' << _SHIP << ' ' << _SHIP << ' ' << "\n";
	gotoxy(30, 8);
	Print_Horizon();	
	gotoxy(30, 9);
	std::cout << " Quantity |       ";
	if (p.Get_Stat().Num_1()) // Если кол-во одноклеточных кораблей > 0
		std::cout << "\033[92m" << p.Get_Stat().Num_1() << "\033[0m        |        ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m        |        ";
	if (p.Get_Stat().Num_2())
		std::cout << "\033[92m" << p.Get_Stat().Num_2() << "\033[0m        |       ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m        |       ";
	if (p.Get_Stat().Num_3())
		std::cout << "\033[92m" << p.Get_Stat().Num_3() << "\033[0m       |       ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m       |       ";
	if (p.Get_Stat().Num_4())
		std::cout << "\033[92m" << p.Get_Stat().Num_4() << "\033[0m";
	else
		std::cout << "\033[91m" << 0 << "\033[0m";
	gotoxy(x, y); // Возвращаем курсор на место, под таблицами
}
