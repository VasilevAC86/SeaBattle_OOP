# include <iostream>
#include<string>
#include<exception>

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
	char choice_placing; // Выбор пользователя типа расстановки кораблей (ручная или автоматическая)
	char choice_player; //Выбор типа противника (игрок или компьютер)
	char choice_move; // Символ игрока, кто начнёт игру
	std::string tmp; // Временная строка (храним всё, что вводит игрок)
	int difficult_level; // Уровень сложности компьютера
	std::getline(std::cin, name_player_1); // Вводим имя игрока 1
	std::cout << "\nHello \033[92m" << name_player_1 << "!\n\n\033[93mChoose who will play with you:\033[0m \npress \033[92m1\033[0m if you'll be playing against the computer OR \npress \033[92many other key\033[0m if you'll be playing with another player.\nYour choice -> ";
	std::cin >> tmp;
	choice_player = EXC(tmp);
	if (choice_player != '1') {
		std::cout << std::endl << "\033[93mEnter your name, second player ->\033[0m ";
		std::cin.ignore();
		std::getline(std::cin, name_player_2);
	}	
	else {
		std::cout << std::endl << "\033[93mSelect computer difficulty level:" << std::endl << "\033[0m" <<\
			"press \033[93m1\033[0m to select a \033[93msimple level\033[0m (the computer is stupid and unlucky)" << std::endl \
			<< "press \033[93m2\033[0m to select a \033[92mmiddle level\033[0m (the computer is an average player)" << std::endl\
			<< "press \033[93m3\033[0m to select a \033[95mdifficult level \033[0m(the computer is very smart and lucky)" \
			<< std::endl << "\033[93mYour choice -> \033[0m";
		std::cin >> tmp;
		try { // Обработка исключения, если игрок ввёл что-то не то
			if (tmp.size() != 1 || tmp.at(0) < 49 || tmp.at(0) > 51)
				throw std::exception("\n\033[91mInput error! The entered value is not an availavle difficult level!\033[0m\n");
		}
		catch (const std::exception& ex) {
			std::cerr << ex.what() << std::endl;
			bool key = false;
			while (!key) {
				std::cout << "Enter \033[4myour choice\033[0m one more time (int from 1 to 3) -> ";
				std::cin >> tmp;
				if (tmp.size() != 1 || tmp.at(0) < 49 || tmp.at(0) > 51)
					key = false;
				else
					key = true;
			}
		}
		difficult_level = stoi(tmp);
	}
	Game G(name_player_1, name_player_2); // Создаём объект "Игра", автоматически создаются все другие объекты игры	
		
	// =================================== Шаг 2 - Подготовка к игре (расстановка кораблей игроками) ===========================

	std::cout << std::endl << "\033[92m" << name_player_1 << "!\033[0m" << std::endl << "\033[93mLet's place ships on the field!\033[0m" << \
		std::endl << "\033[93mChoose a way to place ships on the field:\033[0m \npress \033[92m1\033[0m to manual place ships OR press \033[92many other key\033[0m to automatic ships placement." \
		<< std::endl << "Your choice -> ";
	std::cin >> tmp;
	choice_placing = EXC(tmp);
	system("cls");
	if (choice_placing == '1') // Если выбрана ручная расстановка кораблей		
		G.Hand(true); // Игроку 1 предоставляется возможность заполнить поле
	else
		G.Auto(true); // Автоматическое заполенение игрового поля игрока 1	
	if (choice_player != '1') {		
		std::cout << std::endl << "\033[92m" << name_player_2 << "!\033[0m" << std::endl << "\033[93mLet's place ships on the field!\033[0m" << \
			std::endl << "\033[93mChoose a way to place ships on the field:\033[0m \npress \033[92m1\033[0m to manual place ships OR press \033[92many other key\033[0m to automatic ships placement." \
			<< std::endl << "Your choice -> ";
		std::cin >> tmp;
		choice_placing = EXC(tmp);
		system("cls");
		if (choice_placing == '1') // Если выбрана ручная расстановка кораблей		
			G.Hand(false); // Игроку 2 предоставляется возможность заполнить поле
		else
			G.Auto(false); // Автоматическое заполенение игрового поля игрока 2
	}
	else
		G.Auto(false); // Автоматическое заполенение игрового поля компьютера		
	system("cls");
			
	// ================================== Шаг 3 - Игра ==============================

	std::cout << "\033[92m" << name_player_1 << "\033[0m and \033[92m" << name_player_2 << \
		"\033[0m!\n\n\033[91mTO BATTLE!!!\033[0m\nAnd may the best player win!!!" << std::endl << std::endl \
		<< "\033[93mWho will make the first move?\033[0m\nPress \033[93m1\033[0m if \033[92m" << name_player_1 \
		<< "\033[0m will make the first move OR press \033[93many other key\033[0m if \033[92m" << name_player_2 \
		<< "\033[0m will make the first move\n\nYour choise -> ";
	std::cin >> tmp;
	choice_move = EXC(tmp);
	while (G.P1().Get_Stat().Num_All() != 0 && G.P2().Get_Stat().Num_All() != 0) { // Пока никто не проиграл
		system("cls");
		if (choice_player != '1') { // Режим игры игрок против игрока
			if (choice_move == '1') { // Ход игрока 1
				std::cout << "\033[92m" << name_player_1 << "\033[0m! Are you ready to make a move?" << std::endl << std::endl;
				system("pause");
				G.Move(true);
				choice_move = '0';
			}
			else { // Ход игрока 2
				std::cout << "\033[92m" << name_player_2 << "\033[0m! Are you ready to make a move?" << std::endl << std::endl;
				system("pause");
				G.Move(false);
				choice_move = '1';
			}
		}
		else { // Режим игры игрок против компьютера
			if (choice_move == '1') { // Ход игрока 1				
				G.Move(true);
				choice_move = '0';
			}
			else { // Ход компьютера
				G.Move_Auto(difficult_level);
				choice_move = '1';
			}
		}
	}

	// ============================== Шаг 4 - Подведение итогов ===========================

	system("cls");	
	std::cout << "\033[92mThe game is over!\033[0m" << std::endl;
	if (G.P1().Get_Stat().Num_All() == 0) {
		std::cout << std::endl << "\033[92m" << name_player_1 << "\033[0m! You are loser" << std::endl << std::endl\
			<< "\033[92m" << name_player_2 << "\033[0m! Your are winner!" << std::endl << std::endl;
	}
	else
		std::cout << std::endl << "\033[92m" << name_player_2 << "\033[0m! You are loser" << std::endl << std::endl\
		<< "\033[92m" << name_player_1 << "\033[0m! Your are winner!" << std::endl << std::endl;
	std::cout << "Your final playing fields:" << std::endl << std::endl;	
	G.Print_Final();
	system("pause");
	system("cls");
	std::cout << "\n\033[92mGood bye\033[0m\n";

	return 0;
}

