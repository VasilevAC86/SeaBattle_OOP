#include "Game.hpp"
#include"Ship.hpp"
#include"Output.hpp"

#include<iostream>
#include<string>

/*
* \brief Функция для проверки наличия выбранного игроком типа корабля
*/
int Check_Position_Ship (int pos, Player *p) {
	if (pos == 1)
		if ((*p).Stat().Num_1() < 4)
			(*p).Stat().Change_1();

	return pos;
}

void Game::By_Hand(bool player) {
	// Создаём объект для вывода в консоль инормации об игроке
	Output out;
	std::string position_text; // Переменная для хранения позиции выбранного типа корабля в формате строки, введённой с клавиатуры
	Player* p = nullptr; // Указатель на игрока
	if (player)
		p = &p1_;
	else
		p = &p2_;
	out.Set_Player(p);
	do {
		out.Print();
		std::cout << "\n\033[93mEnter the\033[0m \033[96mposition\033[0m \033[93mnumber of the ship\033[0m -> ";
		std::cin >> position_text;
		// Если ввведённое пользователем значение не входит в диапазон от 1 до 4
		while (position_text.length() > 1 || position_text[0] < 49 || position_text[0] > 52) { 
			std::cout << "\033[91mInput error!\033[0m\nEnter the \033[96mposition\033[0m number of the ship one more time -> ";
			std::cin >> position_text;
		}
		// Переменная для хранения размера корабля (-48 для переконвертирования кода символа в размер корабля)
		int size_ship = stoi(position_text); 
		size_ship = Check_Position_Ship(size_ship, p);
		system("pause");
	} while ((*p).Stat().Num_All() != 10);
}
