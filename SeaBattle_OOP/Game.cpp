﻿#include "Game.hpp"
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

int Check_Position_Ship (std::string &position_text) {
	// Если введённое пользователем значение не в диапазоне от 1 до 4
	while (position_text.length() > 1 || position_text[0] < 49 || position_text[0] > 52) {
		std::cout << "\033[91mInput error!\033[0m" << std::endl << "Enter the \033[96mposition\033[0m number of the ship one more time -> ";
		std::cin >> position_text;
	}
	return(stoi(position_text));
}

int Enter_Row() {
	int row = 1; // Переменная для хранения координаты строки поля
	std::string row_text; // Строка, введённой пользователем (вводим строку для исключения ошибки ввода с крахом программы)
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

int Enter_Col() {
	std::string col_text; // Строка, введённой пользователем (вводим строку для исключения ошибки ввода с крахом программы)
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

void gotoxy(int x, int y) {
	COORD p = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

int Xcoord() {
	CONSOLE_SCREEN_BUFFER_INFO info_x;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_x);
	return info_x.dwCursorPosition.X;
}

int Ycoord() {
	CONSOLE_SCREEN_BUFFER_INFO info_y;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_y);
	return info_y.dwCursorPosition.Y;
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
		int col = Enter_Col(); // Координата столбца
		int row = Enter_Row(); // Координаты строки		
		int num = (*p).Get_Stat().Num_All() - 1; // Локальная переменная для хранения порядкового номера корабля
		// Заполняем данные выбранного пользователем объекта "Корабль"		
		(*p).Set_Field().At_Set_Ship(num).Size(size_ship); // Устанавливаем размер корабля	
		(*p).Set_Field().At_Set_Ship(num).Capacity(size_ship); // Устанавливаем кол-во "живых" клеток корабля
		while(!(*p).Set_Field().Exam_Position(row,col,num)) { // Цикл проверки возможности вставки корабля в (row, col)
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
			std::string tmp; // Временная строка (храним всё, что вводит игрок)
			do {
				std::cout << "\n\033[93mDo you want to rotate the ship?\033[0m ( \033[92m" << _SHIP << "\033[0m - ship's rotation point)" \
					<< std::endl << "Press \033[93m1\033[0m to YES \033[4mor\033[0m press \033[93many other key\033[0m to NO" \
					<< std::endl << "Your choise -> ";
				std::cin >> tmp;
				my_choise = Exc(tmp);
				if (my_choise != '1')
					break;
				(*p).Set_Field().Rotation(row, col, num);				
				system("cls");
				Print_Player_Active(*p);
			} while (my_choise == '1');			
			(*p).Set_Field().At_Set(row, col)->State('1');
		}
	} while ((*p).Get_Stat().Num_All() != _QAUNTITY);
}

/// Функция уставновки корабля на игровое поле при автоматической расстановке кораблей
void Set_Ship(Player* p, int quantity, int size) {
	int row, col; // Координаты клетки вставки корабля	
	for (int j = 0; j < quantity; ++j) { // Устанавливаем корабли
		if (size == 1)
			(*p).Set_Stat().Change_1(); // Изменяем статистику игрока (увеличиваем кол-во установленных кораблей)
		else
			if (size == 2)
				(*p).Set_Stat().Change_2();
			else
				if (size == 3)
					(*p).Set_Stat().Change_3();
				else
					if (size == 4)
						(*p).Set_Stat().Change_4();
		int num = (*p).Get_Stat().Num_All() - 1; // Порядковый номер корабля в массиве fleet_
		(*p).Set_Field().At_Set_Ship(num).Size(size); // Устанавливаем размер корабля
		(*p).Set_Field().At_Set_Ship(num).Capacity(size); // Устанавливаем кол-во "живых" клеток корабля
		do { // Рандомно определяем координаты точки вставки корабля			
			row = rand() % 10;
			col = rand() % 10;
		} while (!(*p).Set_Field().Exam_Position(row, col, num)); // Пока корабль не будет установлен		
	}
}

void Game::Auto(bool player) {
	Player* p = &p1_; // Указатель на игрока, который будет расставлять корабли	
	char my_choice = '1'; // Переменная для хранения выбора пользователя	
	if (!player)
		p = &p2_;
	srand(time(NULL));	
	while(my_choice == '1') { // Цикл формирования игрового поля игрока						
		Set_Ship(p, _QAUNTITY_1, _SIZE_1); // Устанавливаем одноклеточные корабли
		Set_Ship(p, _QAUNTITY_2, _SIZE_2); // Устанавливаем двухклеточные корабли
		Set_Ship(p, _QAUNTITY_4, _SIZE_4); // Устанавливаем четырёхклеточные корабли
		Set_Ship(p, _QAUNTITY_3, _SIZE_3); // Устанавливаем трёхклеточные корабли		
		if ((*p).Name() != "The computer") {
			std::string tmp; // Временная строка (храним всё, что вводит игрок)
			Print_Player_Active((*p));
			std::cout << std::endl << "\033[93mDo you want to change your field?\033[0m" << std::endl << \
				"Press \033[92m'1'\033[0m to re-position ships on the field (You want to change the placement of your fleet) OR"\
				<< std::endl << "Press \033[92many other key\033[0m to exit (if everything suit you)." << std::endl << "Your choice -> ";
			std::cin >> tmp;
			my_choice = Exc(tmp);
			if (my_choice == '1')
				(*p).Clear();
			system("cls");
		}
		else
			my_choice = '0';		
	}		
}

void Game::Move(bool player) {
	Player* p_active = &p1_; // Указатель на игрока, который будет делать ход
	Player* p_passive = &p2_; // Указатель на второго игрока, который ожидает хода
	if (!player) {
		p_active = &p2_;
		p_passive = &p1_;
	}
	system("cls");	
	Print_Player_Active(*p_active);
	std::cout << std::endl;
	Print_Player_Passive(*p_passive);
	std::cout << std::endl << "\033[93mCarry out the shot!\033[0m" << std::endl	<< "Enter the coordinate of the free cell:" << std::endl;		
	bool key = false; // Ключ для повторения хода
	do {
		int col = Enter_Col(); // Координата столбца	
		int row = Enter_Row(); // Координаты строки
		// Если игрок пытается выстрелить в уже прострелянную клетку
		while ((*p_passive).Get_Field().At_Get(row, col).State() == '2' || (*p_passive).Get_Field().At_Get(row, col).State() == '3') {
			std::cout << "\033[91mYour have already shot at the coordinate " << char(col + 65) << row + 1 \
				<< "\033[0m" << std::endl << "Enter the coordinate of the free cell one more time -> ";
			col = Enter_Col();
			row = Enter_Row();
		}
		system("cls");
		if ((*p_passive).Get_Field().At_Get(row, col).State() == '0') { // Если клетка поля противника пустая
			(*p_passive).Set_Field().At_Set(row, col)->State('3'); // Прорисываем объекту Cell(row, col) промах
			(*p_active).Set_Stat().Set_Move();		
			Print_Player_Active(*p_active);
			std::cout << std::endl;
			Print_Player_Passive(*p_passive);
			std::cout << std::endl << "\033[92mMissed!!!\033[0m" << std::endl << std::endl;
			system("pause");
			return;
		}		
		// Если игрок поразил клетку корабля противника, то
		(*p_passive).Set_Field().At_Set(row, col)->State('2'); // Прописываем объекту Cell(row, col) подбитие
		(*p_active).Set_Stat().Set_Move(); // Увеличиваем на 1 счётчик ходов игрока
		int number = (*p_passive).Get_Field().At_Get(row, col).Num_Ship(); // Номер поражённого корабля
		// Уменьшаем кол-во "живых" клеток корабля на 1
		(*p_passive).Set_Field().At_Set_Ship(number).Change_Capacity();
		// Если у поражённого корабля ещё есть "живые" клетки, то присваиваем кораблю статус "раненного"		
		if ((*p_passive).Get_Field().At_Get_Ship(number).Capacity()) {
			(*p_passive).Set_Field().At_Set_Ship(number).State('1');
			std::cout << std::endl << "\033[92mThe enemy ship is wounded! Repeat the move!\033[0m" << std::endl << std::endl;			
		}
		else { // Если "живых" клеток у корабля не осталось, то он убит
			(*p_passive).Set_Field().At_Set_Ship(number).State('0');
			std::cout << std::endl << "\033[92mThe enemy ship destroyed! Repeat the move!\033[0m" << std::endl << std::endl;
			(*p_passive).Set_Field().Snake(number); // Обводим уничтоженный корабль символами "промах"
		}		
		Print_Player_Active(*p_active);
		std::cout << std::endl;
		Print_Player_Passive(*p_passive);		
		key = true;
	} while (key);
}

void Viewer::Print_Player_Active(Player& p) {
	int counter_Cols = 64;// Счётчик букв-координат поля по кодам ASCII-таблицы
	char symbol;// Переменная для хранения буквенной координаты поля
	std::cout << "\033[92m" << p.Name() << "\033[0m!" << "\033[93m Your playing field:\033[0m" << std::endl;
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

void Viewer::Print_Player_Passive(Player& p) {
	int counter_Cols = 64;// Счётчик букв-координат поля по кодам ASCII-таблицы
	char symbol;// Переменная для хранения буквенной координаты поля	
	std::cout << "Your opponent's field (\033[92m" << p.Name() << "'s\033[0m\033[93m field):\033[0m" << std::endl;
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
				if (p.Get_Field().At_Get(i - 1, (j - 3) / 2).State() == '0' || p.Get_Field().At_Get(i - 1, (j - 3) / 2).State() == '1') // Если клетка пустая или занята целым кораблём
					std::cout << "\033[93m_\033[0m";
				else					
					if (p.Get_Field().At_Get(i - 1, (j - 3) / 2).State() == '2') // Если корабль подбит
						std::cout << "\033[91m\033[4m" << 'X' << "\033[0m";					
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
	gotoxy(30, 17);
	std::cout << "\033[93m" << p.Name() << "'s mavailable fleet:\033[0m" << std::endl << std::endl;
	gotoxy(30, 18);
	// Вывод в консоль первой строчки таблицы кораблей
	std::cout << " Position |       \033[96m1\033[0m        |        \033[96m2\033[0m        |       \033[96m3\033[0m       |       \033[96m4\033[0m       \n";
	gotoxy(30, 19);
	Print_Horizon();
	gotoxy(30, 20);
	// Вывод в консоль второй строчки таблицы кораблей
	std::cout << "  Title   | Four-deck ship | Three-deck ship | Two-deck ship | One-deck ship \n";
	gotoxy(30, 21);
	Print_Horizon();
	gotoxy(30, 22);
	// Вывод в консоль третьей строчки таблицы		
	std::cout << "  Image   |       " << _SHIP << "        |       " << _SHIP << ' ' << _SHIP << "       |     " << _SHIP << ' ' << _SHIP << ' ' << _SHIP << "     |    " << _SHIP << ' ' << _SHIP << ' ' << _SHIP << ' ' << _SHIP << ' ' << "\n";
	gotoxy(30, 23);
	Print_Horizon();
	gotoxy(30, 24);
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

void Print_Horizon() {
	for (int i = 0; i < _TABLE_LENGTH; ++i)
		std::cout << '-';
	std::cout << std::endl;
}