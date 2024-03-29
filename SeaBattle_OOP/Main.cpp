# include <iostream>
#include<string>

#include"Game.hpp" // Класс "Игра"
#include"Cell.hpp" // Класс "Клетка"
#include"Ship.hpp" // Класс "Корабль"
#include"Field.hpp" // Класс " Игровое поле"
#include"Player.hpp" // Класс "Игрок"
//#include"Output.hpp" /// Класс для вывода в консоль информации
#include"Statistics.hpp" // Класс для хранения статистики
#include"Global.hpp"

int main() {

	// ======================================= Выбор типа игры и противника ==========================================

	std::cout << "\t\t\033[91mThis is the game 'Sea battle'!\033[0m\n\n\033[93mEnter your name, first player -> \033[0m";
	std::string name_player_1; // Имя игрока 1
	std::string name_player_2 = "The computer"; // Имя игрока 2 (по умолчанию = имя компьютера)
	char choice_placing; // Переменная для хранения выбора пользователя типа расстановки кораблей (ручная или автоматическая)
	char choice_player; // Переменная для хранения выбора типа противника (игрок или компьютер)
	//char choice_first;// Переменная для хранения символа игрока, кто начнёт игру
	//int difficult_level; // Уровень сложности компьютера
	std::getline(std::cin, name_player_1); // Вводим имя игрока 1
	std::cout << "\nHello \033[92m" << name_player_1 << "!\n\n\033[93mChoose who will play with you:\033[0m \npress \033[92m1\033[0m if you'll be playing against the computer OR \npress \033[92many other key\033[0m if you'll be playing with another player.\nYour choice -> ";
	std::cin >> choice_player;
	if (choice_player != 1) {
		std::cout << std::endl << "\033[93mEnter your name, second player ->\033[0m ";
		std::cin.ignore();
		std::getline(std::cin, name_player_2);
	}	
	// Создаём объект "Игра", автоматически создаются все другие объекты игры, за исключением объекта вывода в консоль Output
	Game G(name_player_1, name_player_2);
	//Output out(G.P1()); // Создаём объект для вывода в консоль инормации об игроке
		
	// =================================== Подготовка к игре (расстановка кораблей игроками) ==================================

	std::cout << std::endl << "\033[92m" << name_player_1 << "\033[0m!" << std::endl << "\033[93mLet's place ships on the field!\033[0m" << std::endl << \
		"\033[93mChoose a way to place ships on the field:\033[0m \npress \033[92m1\033[0m to manual place ships OR press \033[92many other key\033[0m to automatic ships placement." \
		<< std::endl << "Your choice -> ";
	std::cin >> choice_placing;
	system("cls");
	if (choice_placing == '1') { // Если выбрана ручная расстановка кораблей
		G.Hand(G.P1()); // Игроку 1 предоставляется возможность заполнить поле первым
	}
	std::cout << std::endl;
	system("pause");
		
	

	return 0;
}