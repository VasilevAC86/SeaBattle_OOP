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
					(*p).Set_Stat().Add_Ship(1); // Увеличиваем общее кол-во кораблей и кол-во одноклеточных кораблей					
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
					(*p).Set_Stat().Add_Ship(2); // Увеличиваем общее кол-во кораблей и кол-во двухклеточных кораблей
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
					(*p).Set_Stat().Add_Ship(3); // Увеличиваем общее кол-во кораблей и кол-во трёхклеточных кораблей
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
					(*p).Set_Stat().Add_Ship(4); // Увеличиваем общее кол-во кораблей и кол-во четырёхклеточных кораблей
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
					<< std::endl << "Your choice -> ";
				std::cin >> tmp;
				my_choise = EXC(tmp);
				if (my_choise != '1')
					break;
				(*p).Set_Field().Rotation(row, col, num);				
				system("cls");
				Print_Player_Active(*p);
			} while (my_choise == '1');			
			(*p).Set_Field().At_Set(row, col)->State('1');
		}
		if ((*p).Get_Stat().Num_All() == _QAUNTITY) {
			system("pause");
			system("cls");
		}
	} while ((*p).Get_Stat().Num_All() != _QAUNTITY);
}

/// Функция уставновки корабля на игровое поле при автоматической расстановке кораблей
void Set_Ship(Player* p, int quantity, int size) {
	int row, col; // Координаты клетки вставки корабля	
	int counter = 0;
	int num; // Порядковый номер корабля в массиве fleet_
	for (int j = 0; j < quantity; ++j) { // Устанавливаем корабли
		(*p).Set_Stat().Add_Ship(size);
		num = (*p).Get_Stat().Num_All() - 1; 
		(*p).Set_Field().At_Set_Ship(num).Size(size); // Устанавливаем размер корабля
		(*p).Set_Field().At_Set_Ship(num).Capacity(size); // Устанавливаем кол-во "живых" клеток корабля
		do { // Рандомно определяем координаты точки вставки корабля			
			row = rand() % 10;
			col = rand() % 10;
			++counter;
			if (counter == 10000)
				break;
		} while (!(*p).Set_Field().Exam_Position(row, col, num)); // Пока корабль не будет установлен
		if (counter == 10000) {
			std::cout << "Something go wrong";
			system("pause");
		}
	}
}

void Game::Auto(bool player) {
	Player* p = &p1_; // Указатель на игрока, который будет расставлять корабли	
	char my_choice = '1'; // Переменная для хранения выбора пользователя	
	if (!player)
		p = &p2_;
	srand(time(NULL));	
	while(my_choice == '1') { // Цикл формирования игрового поля игрока								
		Set_Ship(p, _QAUNTITY_4, _SIZE_4); // Устанавливаем четырёхклеточные корабли
		Set_Ship(p, _QAUNTITY_3, _SIZE_3); // Устанавливаем трёхклеточные корабли
		Set_Ship(p, _QAUNTITY_2, _SIZE_2); // Устанавливаем двухклеточные корабли
		Set_Ship(p, _QAUNTITY_1, _SIZE_1); // Устанавливаем одноклеточные корабли
		if ((*p).Name() != "The computer") {
			std::string tmp; // Временная строка (храним всё, что вводит игрок)
			Print_Player_Active((*p));
			std::cout << std::endl << "\033[93mDo you want to change your field?\033[0m" << std::endl << \
				"Press \033[92m'1'\033[0m to re-position ships on the field (You want to change the placement of your fleet) OR"\
				<< std::endl << "Press \033[92many other key\033[0m to exit (if everything suit you)." << std::endl << "Your choice -> ";
			std::cin >> tmp;
			my_choice = EXC(tmp);
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
	int row, col; // Координаты точки выстрела
	int number; // Номер поражённого корабля
	do { // Пока игрок стреляет без промахов, выполняем тело цикла		
		col = Enter_Col(); // Координата столбца	
		row = Enter_Row(); // Координаты строки
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
			Print_Player_Active(*p_active);
			std::cout << std::endl;
			Print_Player_Passive(*p_passive);
			std::cout << std::endl << "\033[92mMissed!!!\033[0m" << std::endl << std::endl;
			system("pause");
			return;
		}		
		// Если игрок поразил клетку корабля противника, то
		(*p_passive).Set_Field().At_Set(row, col)->State('2'); // Прописываем объекту Cell(row, col) подбитие		
		number = (*p_passive).Get_Field().At_Get(row, col).Num_Ship();		
		(*p_passive).Set_Field().At_Set_Ship(number).Change_Capacity(); // Уменьшаем кол-во "живых" клеток корабля на 1
		// Если у поражённого корабля ещё есть "живые" клетки, то присваиваем кораблю статус "раненного"		
		if ((*p_passive).Get_Field().At_Get_Ship(number).Capacity()) {
			(*p_passive).Set_Field().At_Set_Ship(number).State('1');
			std::cout << "\033[92mThe enemy ship is wounded! Repeat the move!\033[0m" << std::endl << std::endl;			
		}
		else { // Если "живых" клеток у корабля не осталось, то он убит
			(*p_passive).Set_Field().At_Set_Ship(number).State('0');
			(*p_passive).Set_Stat().Pop_Ship((*p_passive).Get_Field().At_Get_Ship(number).Size());
			std::cout << "\033[92mThe enemy ship destroyed! Repeat the move!\033[0m" << std::endl << std::endl;
			(*p_passive).Set_Field().Snake(number); // Обводим уничтоженный корабль символами "промах"
		}
		key = true;
		Print_Player_Active(*p_active);
		std::cout << std::endl;
		Print_Player_Passive(*p_passive);
		std::cout << std::endl;		
		if (!key)
			system("pause");		
		if (p_passive->Get_Stat().Num_All() == 0)
			return;
	} while (key);
}

void Game::Move_Auto(int difficult) {
	srand(time(NULL));	
	int row, col; // Координаты клетки поля	
	bool key = false; // Ключ для повторения хода
	bool wounded = false; // Ключ поиска раненного корабля (false - нет раненого, true - есть)
	do { // Пока ИИ стреляет без промахов, повторяем тело цикла
		system("cls");		
		// Определяем координату выстрела, имитируя поведение реального игрока 
		for (int i = 0; i < _QAUNTITY; ++i) // Если раненный корабль есть, то ИИ пытается его добить
			if (p1_.Get_Field().At_Get_Ship(i).State() == '1') {
				row = p1_.Get_Field().At_Get_Ship(i).Point()->Hor();
				col = p1_.Get_Field().At_Get_Ship(i).Point()->Vert() - 65;
				int size = p1_.Get_Field().At_Get_Ship(i).Size(); // Размер раненного корабля
				// Находим ближайшую от точки вставки клетку раненного корабля, которая уже подбита
				if (p1_.Get_Field().At_Get_Ship(i).Vector() == '>') {
					for (int j = col; j < col + size; ++j)
						if (p1_.Get_Field().At_Get(row, j).State() == '2') {
							col = j;
							break;
						}
				}
				else
					if (p1_.Get_Field().At_Get_Ship(i).Vector() == 'v') {
						for (int j = row; j < row + size; ++j)
							if (p1_.Get_Field().At_Get(j, col).State() == '2') {
								row = j;
								break;
							}
					}
					else
						if (p1_.Get_Field().At_Get_Ship(i).Vector() == '<') {
							for (int j = col; j > col - size; --j)
								if (p1_.Get_Field().At_Get(row, j).State() == '2') {
									col = j;
									break;
								}
						}
						else
							if (p1_.Get_Field().At_Get_Ship(i).Vector() == '^') {
								for (int j = row; j > row - size; --j)
									if (p1_.Get_Field().At_Get(j, col).State() == '2') {
										row = j;
										break;
									}
							}
				// Если у корабля подбита только одна клетка, то ИИ выбирает для выстрела рандомно клетку справа/слева/снизу/сверху
				if (size - p1_.Get_Field().At_Get_Ship(i).Capacity() == 1) {
					int vector = rand() % 4; // Ключ направления выстрела (0 - вправо, 1 - вниз, 2 - влево, 3 - вверх)
					bool flag = false; // Код повтора определения направления выстрела
					do { // Пока не будет определена координата выстрела
						if (vector == 0)
							if (col + 1 == _SIZE || p1_.Get_Field().At_Get(row, col + 1).State() == '2' || p1_.Get_Field().At_Get(row, col + 1).State() == '3') // Выстрел в клетку невозможен
								vector = 1; // Смотрим другое направление
							else {
								++col;
								flag = false; // Координата выстрела определена
							}
						if (vector == 1)
							if (row + 1 == _SIZE || p1_.Get_Field().At_Get(row + 1, col).State() == '2' || p1_.Get_Field().At_Get(row + 1, col).State() == '3')
								vector = 2;
							else {
								++row;
								flag = false;
							}
						if (vector == 2)
							if (col - 1 < 0 || p1_.Get_Field().At_Get(row, col - 1).State() == '2' || p1_.Get_Field().At_Get(row, col - 1).State() == '3')
								vector = 3;
							else {
								--col;
								flag = false;
							}
						if (vector == 3)
							if (row - 1 < 0 || p1_.Get_Field().At_Get(row - 1, col).State() == '2' || p1_.Get_Field().At_Get(row - 1, col).State() == '3') {
								vector = 0;
								flag = true; // Надо повторить поиск координат
							}
							else {
								--row;
								flag = false;
							}
					} while (flag);
				}
				// Если у раненного корабля подбито более одной клетки, то ИИ стреляет рандомно по направлению расположения корабля
				else { 
					int vector = rand() % 2; // Ключ направления выстрела (0 - вправо или вниз, 1 - влево или вверх)
					bool flag = false; // Код повтора определения направления выстрела
					do { // Пока не будет определена координата выстрела
						if (p1_.Get_Field().At_Get_Ship(i).Vector() == '>') {
							if (vector == 0)
								for (int j = col; j < col + size; ++j) {
									if (j == _SIZE || p1_.Get_Field().At_Get(row, j).State() == '3') {
										vector = 1;										
										break;
									}
									if (p1_.Get_Field().At_Get(row, j).State() == '0' || p1_.Get_Field().At_Get(row, j).State() == '1') {
										col = j;
										flag = false;
										break;
									}									
								}								
							if (vector == 1)
								for (int j = col; j > col - size; --j) {
									if (j < 0 || p1_.Get_Field().At_Get(row, j).State() == '3') {
										vector = 0;
										flag = true;
										break;
									}
									if (p1_.Get_Field().At_Get(row, j).State() == '0' || p1_.Get_Field().At_Get(row, j).State() == '1') {
										col = j;
										flag = false;
										break;
									}
								}
						}
						if (p1_.Get_Field().At_Get_Ship(i).Vector() == 'v') {
							if (vector == 0)
								for (int j = row; j < row + size; ++j) {
									if (j == _SIZE || p1_.Get_Field().At_Get(j, col).State() == '3') {
										vector = 1;										
										break;
									}
									if (p1_.Get_Field().At_Get(j, col).State() == '0' || p1_.Get_Field().At_Get(j, col).State() == '1') {
										row = j;
										flag = false;
										break;
									}
								}
							if (vector == 1)
								for (int j = row; j > row - size; --j) {
									if (j < 0 || p1_.Get_Field().At_Get(j, col).State() == '3') {
										vector = 0;
										flag = true;
										break;
									}
									if (p1_.Get_Field().At_Get(j, col).State() == '0' || p1_.Get_Field().At_Get(j, col).State() == '1') {
										row = j;
										flag = false;
										break;
									}
								}
						}
						if (p1_.Get_Field().At_Get_Ship(i).Vector() == '<') {
							if (vector == 0) {
								for (int j = col; j < col + size; ++j) {
									if (j == _SIZE || p1_.Get_Field().At_Get(row, j).State() == '3') {
										vector = 1;
										break;
									}
									if (p1_.Get_Field().At_Get(row, j).State() == '0' || p1_.Get_Field().At_Get(row, j).State() == '1') {
										col = j;
										flag = false;
										break;
									}
								}
							}
							if (vector == 1) {
								for (int j = col; j > col - size; --j) {
									if (j < 0 || p1_.Get_Field().At_Get(row, j).State() == '3') {
										vector = 0;
										flag = true;
										break;
									}
									if (p1_.Get_Field().At_Get(row, j).State() == '0' || p1_.Get_Field().At_Get(row, j).State() == '1') {
										col = j;
										flag = false;
										break;
									}
								}
							}
						}
						if (p1_.Get_Field().At_Get_Ship(i).Vector() == '^') {
							if (vector == 0) {
								for (int j = row; j < row + size; ++j) {
									if (j == _SIZE || p1_.Get_Field().At_Get(j, col).State() == '3') {
										vector = 1;
										break;
									}
									if (p1_.Get_Field().At_Get(j, col).State() == '0' || p1_.Get_Field().At_Get(j, col).State() == '1') {
										row = j;
										flag = false;
										break;
									}
								}
							}
							if (vector == 1) {
								for (int j = row; j > row - size; --j) {
									if (j < 0 || p1_.Get_Field().At_Get(j, col).State() == '3') {
										vector = 0;
										flag = true;
										break;
									}
									if (p1_.Get_Field().At_Get(j, col).State() == '0' || p1_.Get_Field().At_Get(j, col).State() == '1') {
										row = j;
										flag = false;
										break;
									}
								}
							}
						}
					} while (flag);
				}
				wounded = true;
				break;
			}		
		// Если ИИ не нашёл у игрока раненных кораблей, то координату выстрела определям исходя из уровня сложности ИИ
			if (!wounded)
				if (difficult == 3 && p2_.Get_Stat().Useless_Moves() >= 3 || difficult == 2 && p2_.Get_Stat().Useless_Moves() >= 5) {
					int num; // Рандомный номер корабля
					do {
						num = rand() % _QAUNTITY; // (0, 9)
					} while (p1_.Get_Field().At_Get_Ship(num).State() != '2'); // Пока не найден целый корабль
					// Явно указываем координату целого корабля для гарантированного попадания ИИ
					row = p1_.Get_Field().At_Get_Ship(num).Point()->Hor();
					col = p1_.Get_Field().At_Get_Ship(num).Point()->Vert() - 65;
				}
			else // На самом простом уровне	и пока кол-во бесполезных ходов не превысило предела соотв. уровня сложности		 
				do { // координата выстрела определяется полностью рандомно
					row = rand() % 10; // Случайная координата строки поля
					col = rand() % 10; // Случайная координата столбца поля			
				} while (p1_.Get_Field().At_Get(row, col).State() != '0' && p1_.Get_Field().At_Get(row, col).State() != '1');									
		if (p1_.Get_Field().At_Get(row, col).State() == '0') { // Если клетка пустая, то
			p1_.Set_Field().At_Set(row, col)->State('3'); // прописываем промах
			p2_.Set_Stat().Add_Useless_Moves(); // Увеличиваем счётчик бесполезных ходов ИИ
			std::cout << "\033[92m" << p2_.Name() << "\033[0m" << \
				" shot at the cell with the coordinates (" << char(col + 65) << ", " << row + 1 << ") and \033[93mmissed!\033[0m" << std::endl << std::endl;
			Print_Player_Active(p1_);
			std::cout << std::endl;
			Print_Player_Passive(p2_);
			std::cout << std::endl;
			system("pause");
			return;
		}		
		// Если компьютер поразил клетку корабля игрока			
		p1_.Set_Field().At_Set(row, col)->State('2'); // прописываем попадание в клетку			
		int number = p1_.Get_Field().At_Get(row, col).Num_Ship(); // Номер поражённого корабля	
		p1_.Set_Field().At_Set_Ship(number).Change_Capacity(); // Уменьшаем кол-во "живых" клеток корабля на 1
		p2_.Set_Stat().Clear_Useless_Moves(); // Обнуляем счётчик бесполезных ходов ИИ
		// Если у поражённого корабля ещё есть "живые" клетки, то присваиваем кораблю статус "раненного"		
		if (p1_.Get_Field().At_Get_Ship(number).Capacity()) {
			p1_.Set_Field().At_Set_Ship(number).State('1');			
			std::cout << "\033[92m" << p2_.Name() << "\033[0m" << \
				" shot at the cell with the coordinates [" << char(col + 65) << "][" << row + 1 << "] and \033[91mwounded your ship!\033[0m" << std::endl << std::endl;
		}
		else { // Если "живых" клеток у корабля не осталось, то он убит			
			p1_.Set_Field().At_Set_Ship(number).State('0');
			p1_.Set_Stat().Pop_Ship(p1_.Get_Field().At_Get_Ship(number).Size());			
			wounded = false; // убираем метку, чтобы при повторе хода координата выстрела задалась рандомно
			std::cout << "\033[92m" << p2_.Name() << "\033[0m" << \
				" shot at the cell with the coordinates [" << char(col + 65) << "][" << row + 1 << "] and \033[91mdestroyed your ship!!\033[0m" << std::endl << std::endl;
			p1_.Set_Field().Snake(number); // Обводим уничтоженный корабль символами "промах"
		}
		key = true; // повтор хода
		Print_Player_Active(p1_);
		std::cout << std::endl;
		Print_Player_Passive(p2_);		
		std::cout << std::endl;
		system("pause");
		if (p1_.Get_Stat().Num_All() == 0)
			return;
	} while (key);
}

void Game::Print_Final() {
	Print_Player_Active(p1_, 10);
	Print_Player_Active(p2_, 22);
}

void Viewer::Print_Player_Active(Player& p, int coord) {
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
	Print_Table(p, coord);	
}

void Viewer::Print_Player_Passive(Player& p, int coord) {
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
	Print_Table(p, coord);	
}

void Print_Table(Player& p, int coord) {
	int x, y; // Текущие координаты курсора в консоли
	x = Xcoord();
	y = Ycoord();
	gotoxy(30, coord);
	std::cout << "\033[93m" << p.Name() << "'s available fleet:\033[0m" << std::endl << std::endl;
	gotoxy(30, coord + 1);
	// Вывод в консоль первой строчки таблицы кораблей
	std::cout << " Position |       \033[96m1\033[0m        |        \033[96m2\033[0m        |       \033[96m3\033[0m       |       \033[96m4\033[0m       \n";
	gotoxy(30, coord + 2);
	Print_Horizon();
	gotoxy(30, coord + 3);
	// Вывод в консоль второй строчки таблицы кораблей
	std::cout << "  Title   | Four-deck ship | Three-deck ship | Two-deck ship | One-deck ship \n";
	gotoxy(30, coord + 4);
	Print_Horizon();
	gotoxy(30, coord + 5);
	// Вывод в консоль третьей строчки таблицы		
	std::cout << "  Image   |       " << _SHIP << "        |       " << _SHIP << ' ' << _SHIP << "       |     " << _SHIP << ' ' << _SHIP << ' ' << _SHIP << "     |    " << _SHIP << ' ' << _SHIP << ' ' << _SHIP << ' ' << _SHIP << ' ' << "\n";
	gotoxy(30, coord + 6);
	Print_Horizon();
	gotoxy(30, coord + 7);
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