﻿# include <iostream>
#include<string>

#include"Game.hpp" // Класс "Игра"
#include"Cell.hpp" // Класс "Клетка"
#include"Field.hpp" // Класс "Игровое поле"
#include"Player.hpp" // Класс "Игрок"
#include"Statistics.hpp" // Класс для хранения статистики
#include"Ship.hpp" // Класс "Корабль"
#include"Global.hpp" // Файл с глобальными макросами

int main() {

	// ======================================= Шаг 1 - Выбор типа игры и противника ==========================================

	std::cout << "\t\t\033[91mThis is the game 'Sea battle'!\033[0m\n\n\033[93mEnter your name, first player -> \033[0m";
	std::string name_player_1; // Имя игрока 1
	std::string name_player_2 = "The computer"; // Имя игрока 2 (по умолчанию = имя компьютера)
	char choice_placing; // Переменная для хранения выбора пользователя типа расстановки кораблей (ручная или автоматическая)
	char choice_player; // Переменная для хранения выбора типа противника (игрок или компьютер)
	char choice_move;// Переменная для хранения символа игрока, кто начнёт игру
	//int difficult_level; // Уровень сложности компьютера
	std::getline(std::cin, name_player_1); // Вводим имя игрока 1
	std::cout << "\nHello \033[92m" << name_player_1 << "!\n\n\033[93mChoose who will play with you:\033[0m \npress \033[92m1\033[0m if you'll be playing against the computer OR \npress \033[92many other key\033[0m if you'll be playing with another player.\nYour choice -> ";
	std::cin >> choice_player;
	if (choice_player != '1') {
		std::cout << std::endl << "\033[93mEnter your name, second player ->\033[0m ";
		std::cin.ignore();
		std::getline(std::cin, name_player_2);
	}	
	// Создаём объект "Игра", автоматически создаются все другие объекты игры
	Game G(name_player_1, name_player_2);	
		
	// =================================== Шаг 2 - Подготовка к игре (расстановка кораблей игроками) ===========================

	std::cout << std::endl << "\033[92m" << name_player_1 << "!\033[0m" << std::endl << "\033[93mLet's place ships on the field!\033[0m" << \
		std::endl << "\033[93mChoose a way to place ships on the field:\033[0m \npress \033[92m1\033[0m to manual place ships OR press \033[92many other key\033[0m to automatic ships placement." \
		<< std::endl << "Your choice -> ";
	std::cin >> choice_placing;
	system("cls");
	if (choice_placing == '1') // Если выбрана ручная расстановка кораблей		
		G.Hand(true); // Игроку 1 предоставляется возможность заполнить поле
	else
		G.Auto(true); // Автоматическое заполенение игрового поля игрока 1
	if (choice_player != '1') {		
		std::cout << std::endl << "\033[92m" << name_player_2 << "!\033[0m" << std::endl << "\033[93mLet's place ships on the field!\033[0m" << \
			std::endl << "\033[93mChoose a way to place ships on the field:\033[0m \npress \033[92m1\033[0m to manual place ships OR press \033[92many other key\033[0m to automatic ships placement." \
			<< std::endl << "Your choice -> ";
		std::cin >> choice_placing;
		system("cls");
		if (choice_placing == '1') // Если выбрана ручная расстановка кораблей		
			G.Hand(false); // Игроку 2 предоставляется возможность заполнить поле
		else
			G.Auto(false); // Автоматическое заполенение игрового поля игрока 2
	}
	else
		G.Auto(false); // Автоматическое заполенение игрового поля компьютера
			
	// ================================== Шаг 3 - Игра ==============================

	std::cout << "\033[92m" << name_player_1 << "\033[0m and \033[92m" << name_player_2 << \
		"\033[0m!\n\n\033[91mTO BATTLE!!!\033[0m\nAnd may the best player win!!!" << std::endl << std::endl \
		<< "\033[93mWho will make the first move?\033[0m\nPress \033[93m1\033[0m if \033[92m" << name_player_1 \
		<< "\033[0m will make the first move OR press \033[93many other key\033[0m if \033[92m" << name_player_2 \
		<< "\033[0m will make the first move\n\nYour choise -> ";
	std::cin >> choice_move;	
	while (G.P1().Loser() || G.P2().Loser()) {
		system("cls");
		if (choice_move == '1') {
			std::cout << "\033[92m" << name_player_1 << "\033[0m! Are you ready to make a move?" << std::endl << std::endl;
			system("pause");	
			choice_move = '0';
		}
		else {
			std::cout << "\033[92m" << name_player_2 << "\033[0m! Are you ready to make a move?" << std::endl << std::endl;
			system("pause");
			choice_move = '1';
		}		
	}
	

	return 0;
}