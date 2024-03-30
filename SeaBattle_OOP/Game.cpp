#include "Game.hpp"
#include"Global.hpp"
#include"Cell.hpp"
#include"Field.hpp"

#include<Windows.h>
#include<iostream>
#include<string>

/*
* \brief Внешняя функция проверки точки вставки нового корабля
* \details Если точка вставки соприкасается с уже существующим кораблём, или 
* игрок пытается установить корабль в уже занятую клетку, функция возвращает false
*/
bool Exam_Position(Field* p, int row, int col) {
	if ((*p).At_Get(row, col).State() != '0')	// если клетка занята
		return false;	
	// У нас есть размер и адрес точки вращения корабля


	return true;
}

/*
*  Внешняя функция проверки наличия выбранного игроком типа корабля
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

// Первая строчка таблицы доступных кораблей
const std::string _HEADER = " Position |       1        |        2        |       3       |       4       ";
// Длина первой строчки таблицы доступных кораблей
int _TABLE_LENGTH = _HEADER.length(); // Длина таблицы доступных кораблей в символах
// Код символа корабля в занятой клетки из ASCII-таблицы
const char _SHIP = 219;

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
	do { // Цикл заполнения игрового поля кораблями	вручную
		Print_Player_Active(*p);
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
		int row = Enter_Row();
		int col = Enter_Col();
		// Заполняем данные (размер и адрес точки вставки) выбранного пользователем объекта "Корабль"
		(*p).Set_Field().At_Set((*p).Get_Stat().Num_All() - 1)->Size(size_ship); 
		(*p).Set_Field().At_Set((*p).Get_Stat().Num_All() - 1)->Point((*p).Get_Field().At_Set(row, col));
		while(!Exam_Position(&(*p).Set_Field(), row, col)) { // Цикл проверки возможности вставки корабля в (row, col)
			std::cout << std::endl << "\033[91mThe ship can not be positioned at the specified coordinate!" << \
				std::endl << "\033[91mEnter the coordinate one more time." << std::endl;
			row = Enter_Row();
			col = Enter_Col();
		}

		if (size_ship == 1)
			(*p).Set_Field().At_Set(row, col)->State('1');
		else
			(*p).Set_Field().At_Set(row, col)->State('r');
		system("pause");
		system("cls");			
	} while ((*p).Get_Stat().Num_All() != _QAUNTITY);
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
