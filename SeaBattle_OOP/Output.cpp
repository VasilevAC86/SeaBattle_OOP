#include "Output.hpp"

#include<iostream>
#include<Windows.h>
#include<string>

// Глобальные переменные

// Первая строчка таблицы доступных кораблей
const std::string _HEADER = " Position |       1        |        2        |       3       |       4       ";
// Длина первой строчки таблицы доступных кораблей
int _TABLE_LENGTH = _HEADER.length(); // Длина таблицы доступных кораблей в символах
// Код символа корабля в занятой клетки из ASCII-таблицы
const char _SHIP = 219;

/// Функция для перемещения курсора в точку консоли с координатами x, y
void gotoxy(int x, int y) {
	COORD p = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

/// Функция для получения текущей координаты консоли Х
int Xcoord() {
	CONSOLE_SCREEN_BUFFER_INFO info_x;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
	return info_x.dwCursorPosition.X;
}

/// Функция для получения текущей координаты консоли Y
int Ycoord() {
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	return info_y.dwCursorPosition.Y;
}

/// Функция отрисовки горизонтальной черты в таблице доступных кораблей
void Print_Horizon() {
	for (int i = 0; i < _TABLE_LENGTH; ++i)
		std::cout << '-';
	std::cout << std::endl;
}

void Output::Print() {
	int counter_Cols = 64;// Счётчик букв-координат поля по кодам ASCII-таблицы
	char symbol;// Переменная для хранения буквенной координаты поля
	std::cout << "\033[92m" << (*p_).Name() << "\033[0m" << std::endl << "\033[93mYour playing field:\033[0m" << std::endl;
	for (int i = 0; i <= (*(*p_).field()).Size(); ++i) { // 11-ый ряд - это ряд с обозначениями столбцов
		for (int j = 0; j < 23; ++j) { // 23 столбца: 2 под наименования рядов, 10 под ячейки поля, 11 под границы яыеек поля
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
				if ((*(*(*p_).field()).At(i - 1, (j - 3) / 2)).State() == '0') // Если клетка пустая
					std::cout << "\033[93m_\033[0m";
				else
					if ((*(*(*p_).field()).At(i - 1, (j - 3) / 2)).State() == '1') // Если клетка занята "живым" кораблём
						std::cout << _SHIP;
					else
						if ((*(*(*p_).field()).At(i - 1, (j - 3) / 2)).State() == '2') // Если корабль подбит
							std::cout << "\033[91m\033[4m" << 'X' << "\033[0m";
						else  
							std::cout << "\033[94m\033[4m" << '*' << "\033[0m"; // Если промах
			if (i > 0 && i < (*(*p_).field()).Size())
				if (j == 0)
					std::cout << ' ';
				else
					if (j == 1)
						std::cout << "\033[4m" << i << "\033[0m";
			if (i == (*(*p_).field()).Size()) {
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
	/*if ((*p_).Stat().Num_4()) // Если кол-во 4-ёх клеточных кораблей > 0
		std::cout << "\033[92m" << (*p_).Stat().Num_4() << "\033[0m        |        ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m        |        ";
	if ((*p_).Stat().Num_3())
		std::cout << "\033[92m" << (*p_).Stat().Num_3() << "\033[0m        |       ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m        |       ";
	if ((*p_).Stat().Num_2())
		std::cout << "\033[92m" << (*p_).Stat().Num_2() << "\033[0m       |       ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m       |       ";
	if ((*p_).Stat().Num_1())
		std::cout << "\033[92m" << (*p_).Stat().Num_1() << "\033[0m";
	else
		std::cout << "\033[91m" << 0 << "\033[0m";*/
	if ((*(*p_).Stat()).Num_1()) // Если кол-во одноклеточных кораблей > 0
		std::cout << "\033[92m" << (*(*p_).Stat()).Num_1() << "\033[0m        |        ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m        |        ";
	if ((*(*p_).Stat()).Num_2())
		std::cout << "\033[92m" << (*(*p_).Stat()).Num_2() << "\033[0m        |       ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m        |       ";
	if ((*(*p_).Stat()).Num_3())
		std::cout << "\033[92m" << (*(*p_).Stat()).Num_3() << "\033[0m       |       ";
	else
		std::cout << "\033[91m" << 0 << "\033[0m       |       ";
	if ((*(*p_).Stat()).Num_4())
		std::cout << "\033[92m" << (*(*p_).Stat()).Num_4() << "\033[0m";
	else
		std::cout << "\033[91m" << 0 << "\033[0m";
	gotoxy(x, y); // Возвращаем курсор на место, под таблицами
}
