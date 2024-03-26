#include "Game.hpp"
#include"Ship.hpp"
#include"Output.hpp"

#include<iostream>
#include<string>

/*
* \brief Функция для проверки наличия выбранного игроком типа корабля
*/
int Check_Position_Ship (std::string &position_text) {
	// Если введённое пользователем значение не в диапазоне от 1 до 4
	while (position_text.length() > 1 || position_text[0] < 49 || position_text[0] > 52) {
		std::cout << "\033[91mInput error!\033[0m" << std::endl << "Enter the \033[96mposition\033[0m number of the ship one more time -> ";
		std::cin >> position_text;
	}
	return(stoi(position_text));
}

/// Функция определения координаты ряда игрового поля
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

/// Функция определения координаты столбца игрового поля
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

void Game::By_Hand(bool player) {	
	Output out; // Создаём объект для вывода в консоль инормации об игроке
	std::string position_text; // Переменная для хранения позиции выбранного типа корабля в формате строки, введённой с клавиатуры
	Player* p = nullptr; // Указатель на игрока	
	if (player)
		p = &p1_;		
	else
		p = &p2_;
	out.Set_Player(p); // Заполняет объект класса "Статистика" переданным игроком
	do { // Цикл заполнения игрового поля кораблями
		out.Print();
		std::cout << "\n\033[93mEnter the\033[0m \033[96mposition\033[0m \033[93mnumber of the ship\033[0m -> ";
		std::cin >> position_text;				
		int size_ship = Check_Position_Ship(position_text); // Переменная для хранения размера корабля
		bool key = true; // Переменная для хранения кода ошибки (true - корабль можно поставить на поле, false - нельзя)
		// Цикл проверки выбранного пользователем корабля на доступноть его для выбора (есть ли корабль ещё в наличии?)
		// Итогом цикла должен быть разрешённый игрой корабль (размером size_ship) для установки на игровом поле
		do {
			if (size_ship == 1)
				if ((*(*p).Stat()).Num_1() < 4) {
					(*(*p).Stat()).Change_1(); // Увеличиваем общее кол-во кораблей и кол-во одноклеточных кораблей					
					key = true;
				}
				else {
					key = false;
					std::cout << "\033[91mYou don't have any more ships of this type! Choose a different type of ship\033[0m -> ";
					std::cin >> position_text;
					size_ship = Check_Position_Ship(position_text);
				}
			if (size_ship == 2)
				if ((*(*p).Stat()).Num_2() < 3) {
					(*(*p).Stat()).Change_2(); // Увеличиваем общее кол-во кораблей и кол-во одноклеточных кораблей
					key = true;
				}
				else {
					key = false;
					std::cout << "\033[91mYou don't have any more ships of this type! Choose a different type of ship\033[0m -> ";
					std::cin >> position_text;
					size_ship = Check_Position_Ship(position_text);
				}
			if (size_ship == 3)
				if ((*(*p).Stat()).Num_3() < 2) {
					(*(*p).Stat()).Change_3(); // Увеличиваем общее кол-во кораблей и кол-во одноклеточных кораблей
					key = true;
				}
				else {
					key = false;
					std::cout << "\033[91mYou don't have any more ships of this type! Choose a different type of ship\033[0m -> ";
					std::cin >> position_text;
					size_ship = Check_Position_Ship(position_text);
				}
			if (size_ship == 4)
				if ((*(*p).Stat()).Num_4() < 1) {
					(*(*p).Stat()).Change_4(); // Увеличиваем общее кол-во кораблей и кол-во одноклеточных кораблей
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
		(*(*(*p).field()).At(row, col)).State('1');		
		system("pause");
		system("cls");		
		//Cell Point('r', Enter_Row(), Enter_Col()); // Создаём точку вставки корабля
		
		//system("pause");
	} while ((*(*p).Stat()).Num_All() != 10);
}
